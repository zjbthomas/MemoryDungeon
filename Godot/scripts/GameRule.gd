extends Node

class_name GameRule

enum FLOOR_TYPE {NORMAL, CLOWN, EVIL}
enum HERO_TYPE {WIZARD=0,BERSERKER=1,HUNTER=2,MASTER=3}

const MIN_TIME_HARD = 100
const MIN_TIME_EASY = 120

var rows = []

# for a single game - used in new_level()
var floor_type
var n_erase = 2 # ow many identical cards to erase them - MUST be 2 or 3
var n_level_k = 0 # should not be bigger than maxk
var n_level_sp = 0 # should not be bigger than maxsp
var n_pop = 0
var base_time = 0 # TODO: as main timer in game has an interval of 100 ms, the unit for this is 10 seconds
var objective = 0

# used to record and response in the game progress
var cur_n_rows = 0
var flip_state = 1 # MUST be 1, 2 or 3 and represents the state that how many cards is show - 1 to trigger the GUI
var flip1 = -1
var flip2 = -1
var flip3 = -1
var card_remain = 0 # the number of available cards left in the game
var match = -1
var is_combo = false

# variables that interact between the class and the GUI
var score = 0 # R only, add score automatically
var time_remain = 0
var level = 0 # R/W

var found_treasure:bool = false

# Variables for AI parts.
var is_in_ai_mode = false
var is_ai_turn = false # at the beginning is player's turn
var ai_forget_rate = 100 # The maximum value is 100%
var ai_memory = []
var ai_flip_state = 1
var ai_score = 0

# for hero system.
var hero = HERO_TYPE.WIZARD # TODO: WIZARD is the default hero.

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
	
	var n_owned_k = Global.user.get_owned_k().count(true)

	if level % 10 == 0: # an Evil Level
		floor_type = FLOOR_TYPE.EVIL;

		n_erase = 3

		# generate level info
		n_level_k = n_owned_k
		n_level_sp = 2 # REINFORCE and CHAOS
		cur_n_rows = 4
		n_pop = 2

		# calculate time
		base_time = MIN_TIME_HARD + 50 * (n_erase - 2) + 10 * (n_level_k - 2) + 50 * (n_pop - 1) - 2 * (level - 1)

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
		base_time = MIN_TIME_HARD + 50 * (n_erase - 2) + 15 * (n_level_k - 2) + 50 * (n_pop - 1) - 2 * (level - 1)

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
		n_pop = 1 + randi() % 7 * 0.2 # about 83% is 1

		normal_level_default_settings()

	# for MASTER
	if (hero == HERO_TYPE.MASTER):
		time_remain += 30

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
	if (hero == HERO_TYPE.MASTER):
		time_remain += 30

	score = 0
	is_combo = false

	start()

func normal_level_default_settings():
	# generate kinds of spcial cards
	n_level_sp = Global.MAXSP

	# calculate time
	base_time = MIN_TIME_EASY + 50 * (n_erase- 2) + 20 * (n_level_k - 2) + 50 * (n_pop - 1) - 2 * (level - 1)

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
	
	var temp_r = cur_n_rows
	cur_n_rows = 0 # pop_row() will use and modify this value, so we reset it to 0 here
	# TODO; pop_row(temp_r)
	cur_n_rows = temp_r
	
	# TODO: shuffle_cards()
	
	flip_state = 1
	ai_flip_state = 1

## whether a card is clickable or not.
#// Input: the index of a card (need to be decoded).
#// Output: Whether it is clickable or not.
#bool GameRule::isCardClickable(int n)
#{
	#int sr,sc;
	#this->n2RC(n,&sr,&sc);
#
	#if ((this->rowArr[sr].getCardKind(sc)==0)||(this->rowArr[sr].getCardState(sc) == Row::COVER)) {
		#return true;
	#}
	#else if ((this->flipState == 2) && (n == this->flip1)) {
		#return true;
	#}
	#else {
		#return false;
	#}
#}
#
#// Get the state of kind of one card.
#// Input: the index of a card (need to be decoded).
#// Output: If it's a EXISTED special card, return the kind of special card, if it's not uncovered, return state, Otherwise, return kind.
#// Call: n2RC(), row::getkind(), row::getstate().
#int GameRule::getCardDisplay(int n)
#{
	#int sr,sc;
	#n2RC(n,&sr,&sc);
#
	#if (this->rowArr[sr].getCardKind(sc) == 0) // 0 means special kind
	#{
		#// Make TIME of MASTER become visible.
		#if ((this->hero == MASTER)&&(this->rowArr[sr].getSp(sc) == Row::HEAL) && (this->rowArr[sr].getCardState(sc) != Row::NE))
		#{
			#this->rowArr[sr].setCardState(sc, Row::UNCOVER);
			#return this->rowArr[sr].getSp(sc);
		#}
		#if (this->rowArr[sr].getCardState(sc) == Row::UNCOVER)
			#return this->rowArr[sr].getSp(sc);
		#else
			#return this->rowArr[sr].getCardState(sc);
	#}
#
	#if (this->rowArr[sr].getCardState(sc) != Row::UNCOVER)
		#return this->rowArr[sr].getCardState(sc);
	#else
		#return this->rowArr[sr].getCardKind(sc);
#}
#
#// Response to a click.
#// Input: the index of a card (need to be decoded).
#// Output: If a special card is clicked, return the kind of that card; Otherwise, return whether a single card or a pair of cards is clicked.
#// Call: n2RC(), row::getkind(), row::getstate(), row::setstate().
#int GameRule::performClick(int n)
#{
	#int sr,sc;
	#n2RC(n,&sr,&sc);
#
	#// If it is a special card.
	#if (this->rowArr[sr].getCardKind(sc) == 0)
	#{
		#// If a single/double card had been clicked, cover it/them.
		#int tr,tc;
		#switch (this->flipState)
		#{
		#case 2:
			#n2RC(this->flip1, &tr, &tc);
			#this->rowArr[tr].setCardState(tc, Row::COVER);
			#break;
		#case 3:
			#n2RC(this->flip1,&tr,&tc);
			#this->rowArr[tr].setCardState(tc,Row::COVER);
			#n2RC(this->flip2,&tr,&tc);
			#this->rowArr[tr].setCardState(tc,Row::COVER);
			#break;
		#}
#
		#// special card effect
		#// TODO: move this to a single function
		#switch (this->rowArr[sr].getSp(sc))
		#{
		#case Row::REINFORCE:
			#// Minus the score by the number of rows left.
			#if (this->score >= (this->maxR - this->currentR)) {
				#this->score -= (this->maxR - this->currentR);
			#}
			#// Pop a new row and show it.
			#if (this->currentR < this->maxR)
			#{
				#this->popRow(1);
#
				#// Update the value of n as rows are added.
				#n += (this->maxC);
				#n2RC(n,&sr,&sc); // used later which uncover the card
#
				#// uncover newly added row (for user to remember them)
				#for (int c = 0; c < this->maxC; c++) {
					#this->rowArr[this->currentR - 1].setCardState(c, Row::UNCOVER);
				#}
			#}
			#break;{}
		#case Row::CHAOS:
			#this->shuffleCards();
#
			#// show all the cards
			#for (int r = 0; r < this->currentR; r++)
			#{
				#for (int c = 0; c < this->maxC; c++) {
					#if (this->rowArr[r].getCardState(c) != Row::NE) {
						#this->rowArr[r].setCardState(c, Row::UNCOVER);
					#}
				#}
			#}
			#break;
		#case Row::GOLD:
			#// The operations are done in the GUI.
			#break;
		#case Row::MAP:
			#this->match = -1; // we need a class member as it is used in other function
#
			#int nPairs2Match;
			#int tempPos;
#
			#int tempMatch; // we need this as HUNTER will find two pairs
			#tempMatch = -1;
#
			#// decide how many pairs to match
			#if (this->hero == HUNTER) {
				#nPairs2Match = 2;
			#}
			#else {
				#nPairs2Match = 1;
			#}
#
			#// handle each pair
			#for (int p = 0; p < nPairs2Match; p++)
			#{
				#// find one as reference
				#for (int cn = 0; cn < (this->maxR)*(this->maxC); cn++)
				#{
					#n2RC(cn,&tr,&tc);
#
					#if ((this->rowArr[tr].getCardState(tc) != Row::NE) &&
						#(this->rowArr[tr].getCardKind(tc) != 0) &&
						#(this->rowArr[tr].getCardKind(tc) != tempMatch))
					#{
						#this->rowArr[tr].setCardState(tc, Row::UNCOVER);
						#this->match = this->rowArr[tr].getCardKind(tc);
						#tempPos = cn;
						#tempMatch = this->rowArr[tr].getCardKind(tc);
						#break;
					#}
				#}
#
				#// find other cards that match the reference
				#for (int en = this->eraseN; en >= 2; en--) {
					#for (int cn = (tempPos + 1) ; cn < (this->maxR)*(this->maxC); cn++)
					#{
						#n2RC(cn,&tr,&tc);
#
						#if ((this->rowArr[tr].getCardState(tc) != Row::NE) && (this->rowArr[tr].getCardKind(tc) == this->match))
						#{
							#this->rowArr[tr].setCardState(tc, Row::UNCOVER);
							#tempPos = cn;
							#break;
						#}
					#}
				#}
			#}
			#break;
		#case Row::HEAL:
			#if (this->hero == MASTER)
			#{
				#this->timeRemain += (this->baseTime / 2.0);
#
				#if (this->timeRemain > this->baseTime) {
					#this->timeRemain = this->baseTime;
				#}
			#}
			#else {
				#this->timeRemain = this->baseTime;
			#}
			#break;
		#case Row::TREASURE:
			#// The operations are done in the GUI.
			#break;
		#}
#
		#// uncover the special card
		#this->rowArr[sr].setCardState(sc, Row::UNCOVER);
#
		#this->flip1 = n;
		#this->flipState = 1;
#
		#return this->rowArr[sr].getSp(sc); // return the kind of special card.
	#}
#
	#// If it is a normal card.
	#switch (this->flipState)
	#{
	#case 1:
		#this->flip1 = n;
		#(this->flipState)++;
		#break;
	#case 2:
		#this->flip2 = n;
		#if (this->eraseN == 2)
		#{
			#this->flipState = 1;
#
			#// if user click the same card, cover it
			#if (this->flip1 == this->flip2)
			#{
				#this->rowArr[sr].setCardState(sc,Row::COVER);
#
				#return 0;
			#}
		#}
		#else
		#{
			#int sr1,sc1,sr2,sc2;
			#n2RC(this->flip1,&sr1,&sc1);
			#n2RC(this->flip2,&sr2,&sc2);
#
			#if (this->flip1 == this->flip2)
			#{
				#this->rowArr[sr].setCardState(sc,Row::COVER);
#
				#this->flipState = 1;
#
				#return 0;
			#}
#
			#if (this->rowArr[sr1].getCardKind(sc1) != this->rowArr[sr2].getCardKind(sc2))
			#{
				#this->flip3 = n;
#
				#this->flipState = 1;
			#}
			#else
				#(this->flipState)++;
		#}
		#break;
	#case 3:
		#this->flip3 = n;
#
		#(this->flipState)=1;
#
		#break;
	#}
#
	#this->rowArr[sr].setCardState(sc, Row::UNCOVER);
#
	#return ((this->flipState) == 1);
#}
#
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
#// Get the number of rows avaliable in the game. It will also update nowr.
#// Output: the number of rows avaliable in the game.
#int GameRule::updateCurrentR()
#{
	#// find the empty row position
	#// Notice that the row indeces in game are mirrored, which means we find the minimum r with enabled cards
	#int emptyRIndex = 0;
	#for (int r = 0; r < this->currentR; r++)
	#{
		#for (int c = 0; c < this->maxC; c++)
		#{
			#if (this->rowArr[r].getCardState(c) != Row::NE)
			#{
				#emptyRIndex = r;
				#r = this->currentR; // break loop for r as well
				#break;
			#}
		#}
	#}
#
	#// Move the rows to fill the empty row.
	#if (emptyRIndex != 0)
	#{
		#for (int r = emptyRIndex; r < this->currentR; r++)
		#{
			#for (int c = 0; c < this->maxC; c++)
			#{
				#this->rowArr[r - emptyRIndex].setCardState(c,this->rowArr[r].getCardState(c));
				#this->rowArr[r - emptyRIndex].setCardKind(c,this->rowArr[r].getCardKind(c));
				#this->rowArr[r - emptyRIndex].setSp(c,this->rowArr[r].getSp(c));
				#this->rowArr[r].setCardState(c,Row::NE);
			#}
		#}
	#}
#
	#// update currentR
	#(this->currentR) -= emptyRIndex;
#
	#return this->currentR;
#}
#
#// To make a new row available in the game, and decide whether game over.
#// Input: how many rows will be popped in one time.
#// Output: whether game IS NOT over (or rather say, whether a new line is poped).
#// Call: row::setstate().
#bool GameRule::popRow(int n)
#{
	#if ((this->currentR + n) > this->maxR) // Game over.
	#{
		#for (int r = 0; r < this->maxR; r++)
		#{
			#for (int c = 0; c < this->maxC; c++)
				#this->rowArr[r].setCardState(c, Row::NE);
		#}
		#return false;
	#}
	#else
	#{
		#int lastR = this->currentR;
		#int genN = n * this->maxC;
		#// If the number of cards is not devidable by the rule number, add special card.
		#int nRow2AddSp = genN % this->eraseN;
#
		#// add random special card
		#int randomR1 = -1, randomR2 = -1;
		#switch (nRow2AddSp)
		#{
		#case 2:
			#randomR2 = lastR + rand() % n;
#
			#this->rowArr[randomR2].newRow(this->maxK, this->levelKN, this->eraseN, this->levelSpN);
			#for (int c = 0; c < this->maxC; c++) {
				#this->rowArr[randomR2].setCardState(c, Row::COVER);
			#}
#
			#(this->currentR)++;
			#(this->flip1) += this->maxC;
			#(this->flip2) += this->maxC;
			#(this->flip3) += this->maxC;
			#(this->cardRemain) += this->maxC;
#
			#// no break - do case 1 as well
		#case 1:
			#randomR1 = lastR + rand() % n;
			#while (randomR1 == randomR2) {
				#randomR1 = lastR + rand() % n;
			#}
#
			#this->rowArr[randomR1].newRow(this->maxK, this->levelKN, this->eraseN, this->levelSpN);
			#for (int c = 0; c < this->maxC; c++) {
				#this->rowArr[randomR1].setCardState(c, Row::COVER);
			#}
#
			#(this->currentR)++;
			#(this->flip1) += this->maxC;
			#(this->flip2) += this->maxC;
			#(this->flip3) += this->maxC;
			#(this->cardRemain) += this->maxC;
#
			#break;
		#}
#
		#// Generate other rows that without special card.
		#int rowN = n - nRow2AddSp;
		#genN = this->maxC * rowN;
#
		#// Calculate purchased card kinds.
		#// TODO: better to move these into row.cpp
		#int ownedKN = 0;
		#int kLast = 0; // this is used in generating random kind
		#for (int k=0; k < maxK; k++)
		#{
			#if (this->ownedKArr[k])
			#{
				#ownedKN++;
			#}
#
			#// TODO: a trick: first few kinds appear more than later kinds, as we stop when ownedKN == levelK
			#if (ownedKN == this->levelKN)
			#{
				#kLast = k;
				#break;
			#}
		#}
#
		#int* perKNArr = new int[kLast + 1];
		#for (int k = 0; k < kLast; k++)
		#{
			#if ((this->ownedKArr[k]) && (genN >= (this->maxC) * (rowN) / (this->levelKN)))
			#{
				#int nPairs = (this->maxC) * (rowN) / (this->eraseN) / (this->levelKN) + rand() % 2;  // This gives the number of pairs of one kind of cards.
				#while ((nPairs * (this->eraseN)) > genN) {
					#nPairs = (this->maxC) * (rowN) / (this->eraseN) / (this->levelKN) + rand() % 2;
				#}
				#perKNArr[k] = nPairs * this->eraseN;
				#genN -= perKNArr[k];
			#}
			#else
			#{
				#perKNArr[k] = 0;
			#}
		#}
#
		#perKNArr[kLast] = genN;
		#if (rowN != 0)
		#{
			#for (int r = 0; r < n; r++)
			#{
				#if (((lastR + r) != randomR1) && ((lastR + r) != randomR2))
				#{
					#this->rowArr[(lastR + r)].oneRandomRow(kLast, perKNArr);
					#for (int c = 0; c < this->maxC; c++) {
						#this->rowArr[(lastR + r)].setCardState(c, Row::COVER);
					#}
#
					#(this->currentR)++;
					#(this->flip1) += this->maxC;
					#(this->flip2) += this->maxC;
					#(this->flip3) += this->maxC;
					#(this->cardRemain) += this->maxC;
				#}
			#}
		#}
#
		#// reset timer
		#this->timeRemain = this->baseTime;
#
		#return true;
	#}
#}
#
#// Disorganise all existing and avaliable (NOT SPECIAL) cards in the game.
#void GameRule::shuffleCards()
#{
	#int* perKNArr=new int[this->maxK];
	#for (int k = 0; k < this->maxK; k++) {
		#perKNArr[k] = 0;
	#}
#
	#// check and store how many cards per kind
	#for (int r = 0; r < this->currentR; r++)
	#{
		#for (int c = 0; c < this->maxC; c++)
		#{
			#if ((this->rowArr[r].getCardState(c) != Row::NE) && (this->rowArr[r].getCardKind(c) != 0)) {
				#perKNArr[this->rowArr[r].getCardKind(c) - 1]++;
			#}
		#}
	#}
#
	#// shuffle
	#for (int r = 0; r < this->currentR; r++)
	#{
		#this->rowArr[r].shuffle(this->maxK, perKNArr);
	#}
	#delete [] perKNArr;
#}
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
#
#// Get how many rows will pop when time out.
#// Output: the current popn.
#int GameRule::getPopN()
#{
	#return this->popN;
#}
#
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
#// Get how many kinds are purchased.
#// Output: the number of cards purchased by user.
#int GameRule::getOwnedKN()
#{
	#int ownedKN=0;
	#for (int k = 0; k < this->maxK; k++)
	#{
		#if (this->ownedKArr[k])
			#ownedKN++;
	#}
	#return ownedKN;
#}
#
#// Get the current hero.
#// Output: the current hero,
#int GameRule::getHero()
#{
	#return this->hero;
#}
#
#// Set the current hero.
#// Input: the expected hero.
#void GameRule::setHero(int h)
#{
	#this->hero = h;
#}
