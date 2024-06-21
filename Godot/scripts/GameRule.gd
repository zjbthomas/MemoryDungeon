extends Node

class_name GameRule

enum FLOOR_TYPE {NORMAL, CLOWN, EVIL}

# should not overlapped with SP_TYPE
enum CLICK_PERFORMED {
	NO_SETTLEMENT = CardRule.SP_TYPE.TREASURE + 1,
	SETTLEMENT = CardRule.SP_TYPE.TREASURE + 2,
}

const MIN_TIME_HARD = 10
const MIN_TIME_EASY = 12

const ADD_GOLD = 3

var rows = []

# for a single game - used in new_level()
var floor_type
var n_erase:int = 2 # ow many identical cards to erase them - MUST be 2 or 3
var n_level_k = 0 # should not be bigger than maxk
var n_level_sp = 0 # should not be bigger than maxsp
var n_pop:int = 0
var base_time = 0 # TODO: as main timer in game has an interval of 100 ms, the unit for this is 10 seconds
var objective = 0

# used to record and response in the game progress
var cur_n_rows = 0
var flip_state = 0 # represents the state that how many cards is uncovered - MUST be 0, 1 or 2
var flip1 = -1
var flip2 = -1
var flip3 = -1
var card_remain = 0 # the number of available cards left in the game
var matched = -1
var is_combo = false

# variables that interact between the class and the GUI
var score = 0 # R only, add score automatically
var time_remain = 0
var level:int = 0 # R/W

var found_treasure:bool = false

# Variables for AI parts.
var is_in_ai_mode = false
var is_ai_turn = false # at the beginning is player's turn
var ai_forget_rate = 100 # The maximum value is 100%
var ai_memory = []
var ai_flip_state = 0
var ai_score = 0

func _init():
	# initial rows
	for ix in range(Global.MAXR):
		rows.append(RowRule.new())

	# initial AI
	for ix in range(Global.MAXR * Global.MAXC):
		ai_memory.append(false)
	
# Generate a new level.
func new_level():
	# not AI mode
	is_in_ai_mode = false

	level += 1
	
	var n_owned_k = Global.user.owned_k.count(true)

	if level % 10 == 0: # an Evil Level
		floor_type = FLOOR_TYPE.EVIL;

		n_erase = 3

		# generate level info
		n_level_k = n_owned_k
		n_level_sp = 2 # REINFORCE and CHAOS
		cur_n_rows = 4
		n_pop = 2

		# calculate time
		base_time = MIN_TIME_HARD + 5 * (n_erase - 2) + 1 * (n_level_k - 2) + 5 * (n_pop - 1) - 0.2 * (level - 1)

		if (base_time < MIN_TIME_HARD):
			base_time = MIN_TIME_HARD

		time_remain = base_time

		# calculte objective
		objective = 20 + 3 * (level - 1)
	elif (level % 5 == 0): # a Clown Level
		floor_type = FLOOR_TYPE.CLOWN

		n_erase = 2

		# generate level info
		n_level_k = n_owned_k
		n_level_sp = 3 # REINFORCE, CHAOS and GOOD
		cur_n_rows = 3
		n_pop = 1

		# calculate time
		base_time = MIN_TIME_HARD + 5 * (n_erase - 2) + 1.5 * (n_level_k - 2) + 5 * (n_pop - 1) - 0.2 * (level - 1)

		if (base_time < MIN_TIME_HARD):
			base_time = MIN_TIME_HARD

		time_remain = base_time

		# calculte objective
		objective = 20 + 3 * (level - 1)
	else: # a normal Level
		floor_type = FLOOR_TYPE.NORMAL

		# generate the game rule
		n_erase = 2 + randi() % 7 * 0.2 # about 83% is 2

		# generate the kind of card
		n_level_k = 2 + randi() % (n_owned_k - 1)

		# generate beginning number of rows
		cur_n_rows = 2 + randi() % (Global.MAXR - 3)

		# generate how many rows will be popped in one time
		n_pop = 1 + int(randi() % 7 * 0.2) # about 83% is 1

		normal_level_default_settings()

	# for MASTER
	if (Global.user.hero == Global.HERO_TYPE.MASTER):
		time_remain += 3

	score = 0
	is_combo = false

	start()

# Generate a new level by pre-set conditions.
func new_level_by_config(n_erase, n_level_k, cur_n_rows, n_pop):
	is_in_ai_mode = false

	level += 1

	# variables that can be set by user
	self.n_erase = 3
	self.n_level_k = n_level_k
	self.cur_n_rows = cur_n_rows
	self.n_pop = n_pop

	# other variables generated directly by the system
	normal_level_default_settings()

	# for MASTER
	if (Global.user.hero == Global.HERO_TYPE.MASTER):
		time_remain += 30

	score = 0
	is_combo = false

	start()

func normal_level_default_settings():
	# generate kinds of spcial cards
	n_level_sp = Global.MAXSP

	# calculate time
	base_time = MIN_TIME_EASY + 5 * (n_erase- 2) + 2 * (n_level_k - 2) + 5 * (n_pop - 1) - 0.2 * (level - 1)

	if (base_time < MIN_TIME_EASY):
		base_time = MIN_TIME_EASY

	time_remain = base_time

	# calculte objective
	objective = 20 - 5 * (n_erase - 2) + 3 * (level - 1) - 2 * (cur_n_rows - 2)

# start a new game
func start():
	for ir in range(Global.MAXR):
		for ic in range(Global.MAXC):
			rows[ir].set_card_state(ic, CardRule.CARD_STATE.NE)

	card_remain = 0
	
	# when starting a floor, we need to create cur_n_rows rows, so we set it to 0 and pop_row()
	var temp_r = cur_n_rows
	cur_n_rows = 0 # pop_row() will use and modify this value, so we reset it to 0 here
	pop_row(temp_r)
	cur_n_rows = temp_r
	
	shuffle_cards()
	
	flip_state = 0
	ai_flip_state = 0

# make a new row available in the game, and decide whether game over
func pop_row(n_pop_rows):
	if ((cur_n_rows + n_pop_rows) > Global.MAXR):
		# game over, reset the board
		for ir in range(Global.MAXR):
			for ic in range(Global.MAXC):
				rows[ir].set_card_state(ic, CardRule.CARD_STATE.NE)
		return false
	else:
		var last_r = cur_n_rows
		var n_gen = n_pop_rows * Global.MAXC

		# if the number of cards is not devidable by the rule number, add a special card
		var n_sp_rows = n_gen % n_erase

		# add a special card to a RANDOM row
		var random_r1 = null
		var random_r2 = null
		
		for i in range(n_sp_rows):
			var rand = last_r + randi() % n_pop_rows # a random row number
			while (random_r1 != null and rand != random_r1):
				rand = last_r + randi() % n_pop_rows
			
			rows[rand].new_row(n_level_k, n_erase, n_level_sp)
			for ic in range(Global.MAXC):
				rows[rand].set_card_state(ic, CardRule.CARD_STATE.COVER)
				
			cur_n_rows += 1
			
			# add a new row of cards to temporary pointers
			flip1 += Global.MAXC
			flip2 += Global.MAXC
			flip3 += Global.MAXC
			
			card_remain += Global.MAXC
			
			# saved to be used later
			if (random_r1 == null):
				random_r1 = rand
			else:
				random_r2 = rand
		
		# generate other rows that without a special card
		var n_gen_rows = n_pop_rows - n_sp_rows
		n_gen = Global.MAXC * n_gen_rows
		
		# TODO: the following logic is similar to new_row() in RowRule; can we move there?
		# calculate purchased card kinds
		var last_k = Global.user.cal_last_k(n_level_k)
		
		var n_per_k = []
		n_per_k.resize(last_k + 1)
		for ix in range(last_k): # last_k will be handled later
			if (Global.user.owned_k[ix] and (n_gen >= Global.MAXC * n_gen_rows / n_level_k)):
				var n_pairs = Global.MAXC * n_gen_rows / n_erase / n_level_k + randi() % 2 # this gives the number of pairs of one kind of cards
				while ((n_erase * n_pairs) > n_gen):
					n_pairs = Global.MAXC * n_gen_rows / n_erase / n_level_k + randi() % 2
					
				n_per_k[ix] = n_erase * n_pairs
				n_gen -= n_per_k[ix]
			else:
				n_per_k[ix] = 0 # if no owned, set to 0

		# assign card kinds to each position
		n_per_k[last_k] = n_gen # the remaining n_gen
		if (n_gen_rows != 0):
			for ir in range(n_pop_rows):
				if (((last_r + ir) != random_r1) and ((last_r + ir) != random_r2)):
					rows[(last_r + ir)].one_random_row(last_k, n_per_k)
					for ic in range(Global.MAXC):
						rows[(last_r + ir)].set_card_state(ic, CardRule.CARD_STATE.COVER)
				
					cur_n_rows += 1
		
					# add a new row of cards to temporary pointers
					flip1 += Global.MAXC
					flip2 += Global.MAXC
					flip3 += Global.MAXC
					
					card_remain += Global.MAXC
					
		# reset timer
		time_remain = base_time
		
		return true

# shuffle all existing and avaliable (NOT SPECIAL) cards in the game
func shuffle_cards():
	var n_per_k = []
	n_per_k.resize(Global.MAXK)
	
	for ik in range(Global.MAXK):
		n_per_k[ik] = 0
#
	# check and store how many cards per kind
	for ir in range(cur_n_rows):
		for ic in range(Global.MAXC):
			if (rows[ir].get_card_state(ic) != CardRule.CARD_STATE.NE and !rows[ir].is_sp(ic)):
				n_per_k[rows[ir].get_card_type(ic) - CardRule.OFFSET - 1] += 1

	# shuffle
	for ir in range(cur_n_rows):
		rows[ir].shuffle(n_per_k)

# get the number of rows avaliable in the game; also update cur_n_rows
func update_cur_n_rows():
	# find the empty row position
	# notice that the row indeces in game are mirrored, which means we find the minimum r with enabled cards
	var empty_r_ix = 0
	for ir in range(cur_n_rows):
		for ic in range(Global.MAXC):
			if (rows[ir].get_card_state(ic) != CardRule.CARD_STATE.NE):
				empty_r_ix = ir
				ir = cur_n_rows # TODO: this is for breaking the ir loop as well
				break

	# move the rows to fill the empty row
	if (empty_r_ix != 0):
		for ir in range(empty_r_ix, cur_n_rows):
			for ic in range(Global.MAXC):
				rows[ir - empty_r_ix].set_card_state(ic, rows[ir].get_card_state(ic))
				rows[ir - empty_r_ix].set_card_type(ic, rows[ir].get_card_type(ic))
				
				rows[ir].set_card_state(ic, CardRule.CARD_STATE.NE)
#
	# update cur_n_rows
	cur_n_rows -= empty_r_ix
	
	return cur_n_rows

func rc_to_n(ir, ic):
	return ir * Global.MAXC + ic

func n_to_rc(n):
	var r:int = n / Global.MAXC
	var c:int = n % Global.MAXC
	
	# TODO: do we need to mirror the row?
	
	return [r, c]

# response to a click.
# if a special card is clicked, return the kind of that card; Otherwise, return whether a single card or a pair of cards is clicked
func perform_click(ir, ic):
	# if it is a special card
	if (rows[ir].is_sp(ic)):
		# cover previously clicked cards
		# TODO: may be we can use function to group each of the following operations
		match (flip_state):
			1:
				var tr = n_to_rc(flip1)[0]
				var tc = n_to_rc(flip1)[1]
				rows[tr].set_card_state(tc, CardRule.CARD_STATE.COVER)
			2:
				var tr = n_to_rc(flip1)[0]
				var tc = n_to_rc(flip1)[1]
				rows[tr].set_card_state(tc, CardRule.CARD_STATE.COVER)
				
				tr = n_to_rc(flip2)[0]
				tc = n_to_rc(flip2)[1]
				rows[tr].set_card_state(tc, CardRule.CARD_STATE.COVER)
	
		# special card effect
		# TODO: move this to a single function
		match (rows[ir].get_card_type(ic)):
			CardRule.SP_TYPE.REINFORCE:
				# effect 1: minus the score by the number of rows left
				if (score >= (Global.MAXR - cur_n_rows)):
					score -= (Global.MAXR - cur_n_rows)
				
				# effect 2: pop a new row and show it
				if (cur_n_rows < Global.MAXR):
					pop_row(1)
					
					# update the row number as new row is added
					ir += 1 # TODO: is this correct and why we need this?
					
					# uncover newly added row
					for ic_new in range(Global.MAXC):
						rows[cur_n_rows - 1].set_card_state(ic_new, CardRule.CARD_STATE.UNCOVER)
				
				# effect 3: for HUNTER, decrease gold
				if (Global.user.hero == Global.HERO_TYPE.HUNTER and Global.user.gold >= 1):
					Global.user.gold -= 1
					Global.user.save_game() # TODO: is it too frequent?
			CardRule.SP_TYPE.CHAOS:
				# effect 1: shuffle all cards
				shuffle_cards()
				
				# effect 2: show all cards
				for ir_all in range(cur_n_rows):
					for ic_all in range(Global.MAXC):
						if (rows[ir_all].get_card_state(ic_all) != CardRule.CARD_STATE.NE):
							rows[ir_all].set_card_stete(ic_all, CardRule.CARD_STATE.UNCOVER)
							
				# effect 3: for HUNTER, decrease gold
				if (Global.user.hero == Global.HERO_TYPE.HUNTER and Global.user.gold >= 1):
					Global.user.gold -= 1
					Global.user.save_game() # TODO: is it too frequent?
			CardRule.SP_TYPE.GOLD:
				# effect 1: add golds
				Global.user.gold += ADD_GOLD
				
				# effect 2: for HUNTER, add more gold
				if (Global.user.hero == Global.HERO_TYPE.HUNTER):
					Global.user.gold += ADD_GOLD
					
				Global.user.save_game() # TODO: is it too frequent?
			CardRule.SP_TYPE.MAP:
				matched = -1 # TODO: why class member here? Where it is used?
				
				var n_pairs
				var temp_pos
				
				var temp_matched = -1 # for HUNTER who finds two pairs
			
				# how many pairs to match
				if (Global.user.hero == Global.HERO_TYPE.HUNTER):
					n_pairs = 2
				else:
					n_pairs = 1	

				# find pairs
				for ip in range(n_pairs):
					# find one card first
					for fn in range(Global.MAXR * Global.MAXC): # we use multiplication here so we only need to break one loop
						var ir_find = n_to_rc(fn)[0]
						var ic_find = n_to_rc(fn)[1]

						if (rows[ir_find].get_card_state(ic_find) != CardRule.CARD_STATE.NE and 
							!rows[ir_find].is_sp(ic_find) and
							rows[ir_find].get_card_type(ic_find) != temp_matched):
								rows[ir_find].set_card_state(ic, CardRule.CARD_STATE.UNCOVER)
								matched = rows[ir_find].get_card_type(ic_find)
								temp_pos = fn
								temp_matched = rows[ir_find].get_card_type(ic_find)
								break

					# find other cards that match the reference
					for en in range(n_erase, 2 - 1, -1): # [3, 2]
						for fn in range(temp_pos + 1, Global.MAXR * Global.MAXC): # we use multiplication here so we only need to break one loop
							var ir_find = n_to_rc(fn)[0]
							var ic_find = n_to_rc(fn)[1]
							
							if (rows[ir_find].get_card_state(ic_find) != CardRule.CARD_STATE.NE and 
								rows[ir_find].get_card_type(ic_find) == matched):
									rows[ir_find].set_card_state(ic_find, CardRule.CARD_STATE.UNCOVER)
									temp_pos = fn
									
									break
					
			CardRule.SP_TYPE.HEAL:
				if (Global.user.hero == Global.HERO_TYPE.MASTER):
					# less effective for MASTER
					time_remain += base_time / 2
					
					if (time_remain > base_time):
						time_remain = base_time
				else:
					time_remain = base_time
			CardRule.SP_TYPE.TREASURE:
				# effect 1: found treasure
				found_treasure = true
				
				# effect 2: for HUNTER, add gold
				if (Global.user.hero == Global.HERO_TYPE.HUNTER):
					Global.user.gold += 1
					Global.user.save_game() # TODO: is it too frequent?

		# uncover the special card
		rows[ir].set_card_state(ic, CardRule.CARD_STATE.UNCOVER)
		
		flip1 = rc_to_n(ir, ic)
		flip_state = 1 # TODO: check if this one is correct
		
		return rows[ir].get_card_type(ic) # return the kind of special card
#
	# if it is a normal card
	# no matter how, uncover it
	rows[ir].set_card_state(ic, CardRule.CARD_STATE.UNCOVER)
	
	match (flip_state):
		0:
			flip1 = rc_to_n(ir, ic)
			flip_state = 1
			return CLICK_PERFORMED.NO_SETTLEMENT
		1:
			flip2 = rc_to_n(ir, ic)
			
			if (n_erase == 2):
				
				# user click the same card, cover it
				if (flip1 == flip2):
					rows[ir].set_card_state(ic, CardRule.CARD_STATE.COVER)
					
					flip_state = 0
					
					return CLICK_PERFORMED.NO_SETTLEMENT
				else:
					return CLICK_PERFORMED.SETTLEMENT
					
			else: # n_erase == 3
				var tr1 = n_to_rc(flip1)[0]
				var tc1 = n_to_rc(flip1)[1]
				var tr2 = n_to_rc(flip2)[0]
				var tc2 = n_to_rc(flip2)[1]
				
				# user click the same card, cover it
				if (flip1 == flip2):
					rows[ir].set_card_state(ic, CardRule.CARD_STATE.COVER)
					
					flip_state = 0
					
					return CLICK_PERFORMED.NO_SETTLEMENT
				
				if (rows[tr1].get_card_type(tc1) != rows[tr2].get_card_type(tc2)):
					# user click different cards, but they are different types
					flip3 = rc_to_n(ir, ic) # TODO: why?
					
					flip_state = 2 # TODO: is this correct? Or should be 0? I believe for settlement, this should be reset later...
					
					return CLICK_PERFORMED.SETTLEMENT # settle to show the two wrongly clicked cards for user to remember
				else:
					flip_state = 2
					
		3:
			flip3 = rc_to_n(ir, ic)
			
			return CLICK_PERFORMED.SETTLEMENT

#// When a hint or a pair of cards are shown for a given time, decide what to do next. Used in the closing timer.
#// Input: A pointer pointed to a boolean whether game wins or not.
#// Output: The number of row is available in the game and a boolean pointer.
#// Call: n2RC(), row::getkind(), row::row::getstate(), row::setstate().
#int GameRule::settle(bool* winGame,int* status)
#{
	#*status = EMPTY;
#
	#int sr1,sc1,sr2,sc2,sr3,sc3;
	#n2RC(this->flip1,&sr1,&sc1);
#
	#// If it is a special card.
	#if (this->rowArr[sr1].getCardKind(sc1) == 0)
	#{
		#*status = BONUS;
		#switch (this->rowArr[sr1].getSp(sc1))
		#{
		#case Row::REINFORCE:
			#// cover the newly added row
			#for (int c = 0; c < this->maxC; c++) {
				#this->rowArr[this->currentR - 1].setCardState(c, Row::COVER);
			#}
#
			#if (this->score > 0) {
				#(this->score)--;
			#}
#
			#*status=BREAK;
#
			#break;
#
		#case Row::CHAOS:
			#// cover all the cards
			#for (int r=0; r < this->maxR; r++)
			#{
				#for (int c = 0; c < this->maxC; c++)
				#{
					#if (this->rowArr[r].getCardState(c) != Row::NE) {
						#this->rowArr[r].setCardState(c, Row::COVER);
					#}
				#}
			#}
			#break;
#
		#case Row::GOLD:
			#*status = CREDIT;
			#break;
#
		#case Row::MAP:
			#// when a match is found, remove the matched cards
			#if (this->match != -1)
			#{
				#for (int cn = 0; cn < (this->maxR)*(this->maxC); cn++)
				#{
					#int tr,tc;
					#n2RC(cn,&tr,&tc);
					#if ((this->rowArr[tr].getCardState(tc) == Row::UNCOVER) && (this->rowArr[tr].getCardKind(tc) != 0))
					#{
						#this->rowArr[tr].setCardState(tc, Row::NE);
#
						#(this->cardRemain)--;
					#}
				#}
			#}
#
			#(this->score)++;
#
			#break;
		#case Row::HEAL:
			#break;
		#case Row::TREASURE:
			#break;
		#}
#
		#this->rowArr[sr1].setCardState(sc1,Row::NE);
#
		#//(this->score)++;
		#(this->cardRemain)--;
	#}
	#else
	#{
		#// it is a normal card
		#n2RC(this->flip2,&sr2,&sc2);
		#n2RC(this->flip3,&sr3,&sc3);
#
		#switch (this->eraseN)
		#{
		#case 2:
			#if (this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2))
			#{
				#// remove two cards
				#this->rowArr[sr1].setCardState(sc1, Row::NE);
				#this->rowArr[sr2].setCardState(sc2, Row::NE);
#
				#// add score
				#(this->score)++;
#
				#*status=SCORE;
#
				#// handle combo except BERSERKER
				#if (this->hero != BERSERKER)
				#{
					#if (this->isCombo)
					#{
						#// add one more score
						#(this->score)++;
#
						#*status=COMBO;
					#}
					#else
						#this->isCombo = true;
				#}
				#else
				#{
					#// CRITICAL system for BERSERKER.
					#int criticalRoll = rand() % 100 + 1;
					#if (criticalRoll <= this->CRITICALRATE) // Here set the critical rate.
					#{
						#// add 2 points
						#(this->score)+=2;
#
						#*status=CRITICAL;
					#}
				#}
#
				#// update remaining card number
				#(this->cardRemain) -= (this->eraseN);
#
			#}
			#else
			#{
				#// cover cards if not matched
				#this->rowArr[sr1].setCardState(sc1, Row::COVER);
				#this->rowArr[sr2].setCardState(sc2, Row::COVER);
#
				#// reset combo flag
				#this->isCombo=false;
			#}
			#break;
		#case 3:
			#if ((this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2)) &&
				#(this->rowArr[sr1].getCardKind(sc1)==this->rowArr[sr3].getCardKind(sc3)))
			#{
				#this->rowArr[sr1].setCardState(sc1,Row::NE);
				#this->rowArr[sr2].setCardState(sc2,Row::NE);
				#this->rowArr[sr3].setCardState(sc3,Row::NE);
#
				#// add score
				#(this->score)++;
#
				#*status=SCORE;
#
				#// handle combo except BERSERKER
				#if (this->hero != BERSERKER)
				#{
					#if (this->isCombo)
					#{
						#// add one more score
						#(this->score)++;
#
						#*status=COMBO;
					#}
					#else
						#this->isCombo = true;
				#}
				#else
				#{
					#// CRITICAL system for BERSERKER.
					#int criticalRoll = rand() % 100 + 1;
					#if (criticalRoll <= this->CRITICALRATE) // Here set the critical rate.
					#{
						#// add 2 points
						#(this->score)+=2;
#
						#*status=CRITICAL;
					#}
				#}
#
				#// update remaining card number
				#(this->cardRemain) -= (this->eraseN);
			#}
			#else
			#{
				#this->rowArr[sr1].setCardState(sc1,Row::COVER);
				#this->rowArr[sr2].setCardState(sc2,Row::COVER);
				#this->rowArr[sr3].setCardState(sc3,Row::COVER);
#
				#// reset combo flag
				#this->isCombo=false;
			#}
			#break;
		#}
	#}
#
	#// after removing cards, move remaining cards downwards
	#this->moveCardsDownwards();
#
	#// when the game is not end but no card left, pop new rows
	#if (this->cardRemain == 0)
	#{
		#// Pop half of maximum rows right now, and the left time will change into score.
		#(this->score) += (this->timeRemain) / 10; // TODO: a magic number here
#
		#*status = BONUS;
#
		#this->popRow(this->maxR / 2);
#
		#this->shuffleCards();
	#}
#
	#// win game
	#if ((this->score) >= (this->objective))
	#{
		#*winGame = true;
#
		#// remove all cards
		#for (int n = 0; n < (this->maxR) * (this->maxC); n++)
		#{
			#n2RC(n,&sr1,&sc1);
			#this->rowArr[sr1].setCardState(sc1,Row::NE);
		#}
	#}
	#else {
		#*winGame=false;
	#}
#
	#return this->updateCurrentR();
#}
#
#// The card will move downwards if there is no card below.
#int GameRule::moveCardsDownwards()
#{
	#// Notice that the row indeces in game are mirrored.
	#for (int r = 0; r < this->currentR ;r++)
	#{
		#for (int c=0; c < this->maxC; c++)
		#{
			#if (this->rowArr[r].getCardState(c) != Row::NE)
			#{
				#for (int tr = r + 1; tr < this->currentR; tr++)
				#{
					#if (this->rowArr[tr].getCardState(c) == Row::NE)
					#{
						#this->rowArr[tr].setCardState(c, this->rowArr[r].getCardState(c));
						#this->rowArr[tr].setCardKind(c,this->rowArr[r].getCardKind(c));
						#this->rowArr[tr].setSp(c,this->rowArr[r].getSp(c));
						#this->rowArr[r].setCardState(c, Row::NE);
						#break;
					#}
				#}
			#}
		#}
	#}
	#return this->updateCurrentR(); // This is a MUST!!
#}
#



#
#// Get the rule.
#// Output: the number represent the rule.
#int GameRule::getEraseN()
#{
	#return this->eraseN;
#}
#
#// Get how many kinds is at the game.
#// Output: the current number of kinds.
#int GameRule::getLevelKN()
#{
	#return this->levelKN;
#}

#// Get the base time.
#// Output: the current basetime.
#int GameRule::getBaseTime()
#{
	#return this->baseTime;
#}
#
#// Get the score.
#// Output: the score.
#int GameRule::getObjective()
#{
	#return this->objective;
#}
#
#// Get the score.
#// Output: the current score.
#int GameRule::getScore()
#{
	#return this->score;
#}
#
#// Get the left time.
#// Output: the left time.
#int GameRule::getTimeRemain()
#{
	#return this->timeRemain;
#}
#
#// Set the left time.
#// Input: which time to set.
#void GameRule::setTimeRemain(int t)
#{
	#this->timeRemain = t;
#}
#
#// Get the level.
#// Output: the current level.
#int GameRule::getLevel()
#{
	#return this->level;
#}
#
#// Set the level.
#// Input: which level.
#void GameRule::setLevel(int l)
#{
	#this->level = l;
#}
#
#// Decode an index to row and column.
#// Input: index and two return pointers.
#void GameRule::n2RC(int n, int* sr, int* sc)
#{
	#*sr = n / (this->maxC);
	#*sc = n % (this->maxC);
#
	#// Mirrored the rows which is avaliable in the game.
	#if (*sr < this->currentR) {
		#*sr = this->currentR - (*sr + 1);
	#}
#}
#
#// Start a new AI game.
#// Input: the expected forget percentage of the AI.
#void GameRule::newAILevel(int forgetRate)
#{
	#this->isAIMode = true;
#
	#// Initialize the AI system.
	#this->aiForgetRate = forgetRate;
#
	#for (int n = 0; n < (this->maxR) * (this->maxC); n++) {
		#this->aiMemoryArr[n] = false;
	#}
#
	#this->aiScore = 0;
#
	#// Start a new game.
	#this->isAITurn = false;
#
	#this->eraseN = 2; // force to only match 2 cards
#
	#int ownedKN = 0;
	#for (int k = 0; k < this->maxK; k++)
	#{
		#if (this->ownedKArr[k]) {
			#ownedKN++;
		#}
	#}
	#this->levelKN = ownedKN;
#
	#this->levelSpN = 0; // no special card
#
	#this->currentR = this->maxR; // all rows used
#
	#this->score = 0;
#
	#this->start();
#}
#
#// Do an AI click action.
#// Output: the index number of the progress.
#int GameRule::aiAction()
#{
	#int sr,sc;
#
	#// First the AI will forget some EXISTED cards if it is its first click.
	#// Change the forget percentage into an effective one.
	#int rememberN=0;
	#for (int n = 0; n < (this->maxR) * (this->maxC); n++)
	#{
		#n2RC(n,&sr,&sc);
		#if ((this->aiMemoryArr[n]) && (this->rowArr[sr].getCardState(sc) != Row::NE)) {
			#rememberN++;
		#}
	#}
#
	#int effectiveForgetRate;
	#if (rememberN == 0) {
		#effectiveForgetRate = this->aiForgetRate;
	#}
	#else {
		#effectiveForgetRate = 100 - pow((float)(100 - (this->aiForgetRate)) /100.0 , 1.0 / (float)rememberN) * 100;
	#}
#
	#// a histogram of card kinds that AI remember
	#int* aiPerKNArr = new int[this->maxK];
	#for (int k = 0; k < this->maxK; k++) {
		#aiPerKNArr[k]=0;
	#}
#
	#for (int n = 0; n < (this->maxR) * (this->maxC); n++)
	#{
		#n2RC(n,&sr,&sc);
		#if ((this->aiMemoryArr[n]) && (this->rowArr[sr].getCardState(sc) != Row::NE))
		#{
			#// AI will first forget some cards
			#int forgetRoll = rand() % 100 + 1;
			#if ((forgetRoll <= effectiveForgetRate) &&
				#(this->aiFlipState == 1)) { // will not forget when AI is in action
				#this->aiMemoryArr[n] = false;
			#}
			#else
			#{
				#aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1]++;
			#}
		#}
	#}
#
	#// Then the AI will click a card.
	#// first check whether the AI remember two identical cards.
	#int possibleK=0;
	#for (int k = 0; k < this->maxK; k++)
	#{
		#if (aiPerKNArr[k] >= 2) // TODO: safe to change this to eraseN?
		#{
			#possibleK = k + 1; // an offset 1 is added as 0 is special kind
			#break;
		#}
	#}
#
	#switch (this->aiFlipState)
	#{
	#case 1:
		#if (possibleK != 0)
		#{
			#for (int n = 0; n < (this->maxR) * (this->maxC); n++)
			#{
				#n2RC(n,&sr,&sc);
				#if ((this->aiMemoryArr[n]) &&
					#(this->rowArr[sr].getCardState(sc) != Row::NE) &&
					#(this->rowArr[sr].getCardKind(sc) == possibleK))
				#{
					#this->performClick(n);
					#break;
				#}
			#}
		#}
		#else
		#{
			#// Randomly click a card that it does not remember.
			#int clickPos = rand() % ((this->maxR) * (this->maxC));
			#n2RC(clickPos,&sr,&sc);
			#while ((this->aiMemoryArr[clickPos]) || (this->rowArr[sr].getCardState(sc) == Row::NE))
			#{
				#clickPos = rand() % ((this->maxR) * (this->maxC));
				#n2RC(clickPos,&sr,&sc);
			#}
#
			#this->performClick(clickPos);
#
			#// update memory
			#this->aiMemoryArr[clickPos] = true;
#
			#// if AI now remembers a pair
			#aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1]++;
#
			#// TODO: do we really need the following two lines?
			#if (aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1] >= 2) // TODO: safe to change this to eraseN?
				#possibleK = this->rowArr[sr].getCardKind(sc);
		#}
#
		#(this->aiFlipState)++;
		#break;
	#case 2:
		#if (possibleK != 0)
		#{
			#for (int n = 0; n < (this->maxR) * (this->maxC); n++)
			#{
				#n2RC(n,&sr,&sc);
				#if ((this->aiMemoryArr[n]) &&
					#(this->rowArr[sr].getCardState(sc) != Row::NE) &&
					#(this->rowArr[sr].getCardKind(sc) == possibleK) &&
					#(n != this->flip1)) // will not click the same card that is already uncovered
				#{
					#this->performClick(n);
					#break;
				#}
			#}
		#}
		#else
		#{
			#// Randomly click a card that it does not remember.
			#int clickPos = rand() % ((this->maxR) * (this->maxC));
			#n2RC(clickPos,&sr,&sc);
			#while ((this->aiMemoryArr[clickPos]) ||
				   #(this->rowArr[sr].getCardState(sc) == Row::NE) ||
				   #(clickPos == this->flip1))
			#{
				#clickPos = rand() % ((this->maxR) * (this->maxC));
				#n2RC(clickPos,&sr,&sc);
			#}
#
			#this->performClick(clickPos);
#
			#this->aiMemoryArr[clickPos] = true;
		#}
#
		#(this->aiFlipState)++;
		#break;
#
	#case 3:
		#this->aiFlipState = 1;
		#break;
	#}
#
	#delete [] aiPerKNArr;
	#return this->aiFlipState;
#
#}
#
#// A closing function that designed dedicately for AI.
#// Input: A pointer pointed to a boolean whether game wins or not.
#// Output: The number of row is available in the game and a boolean pointer.
#int GameRule::settleAI(bool* winGame,int* status)
#{
	#*status = EMPTY;
#
	#int sr1,sc1,sr2,sc2;
	#n2RC(this->flip1,&sr1,&sc1);
	#n2RC(this->flip2,&sr2,&sc2);
#
	#if (this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2))
	#{
		#this->rowArr[sr1].setCardState(sc1,Row::NE);
		#this->rowArr[sr2].setCardState(sc2,Row::NE);
#
		#if (this->isAITurn == false)
		#{
			#(this->score)++;
			#*status=SCORE;
		#}
		#else
		#{
			#(this->aiScore)++;
			#*status=AISCORE;
		#}
#
		#(this->cardRemain) -= (this->eraseN);
	#}
	#else
	#{
		#this->rowArr[sr1].setCardState(sc1,Row::COVER);
		#this->rowArr[sr2].setCardState(sc2,Row::COVER);
#
		#// AI remembers all opened cards
		#this->aiMemoryArr[this->flip1]=true;
		#this->aiMemoryArr[this->flip2]=true;
#
		#// if one fails to match cards, swap turn
		#this->isAITurn = !(this->isAITurn);
	#}
#
	#// win game
	#// TODO: why this logic?
	#if (this->cardRemain == 0)
		#*winGame=true;
	#else
		#*winGame = false;
#
	#return this->updateCurrentR();
#}
#
#// Get whether AI system is on or off.
#// Output: the state of the AI system.
#bool GameRule::getIsAIMode()
#{
	#return this->isAIMode;
#}
#
#// Get who is controlling the game.
#// Output: a Boolean to show who is controlling the game.
#bool GameRule::getIsAITurn()
#{
	#return this->isAITurn;
#}
#
#// Get the score of the AI.
#// Output: the score of the AI.
#int GameRule::getAIScore()
#{
	#return this->aiScore;
#}
#

