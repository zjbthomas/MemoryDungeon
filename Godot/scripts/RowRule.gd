extends Node

class_name RowRule

var cards = []

func get_card_state(pos):
	return cards[pos].get_state()
	
func set_card_state(pos, s):
	cards[pos].set_state(s)

func get_card_type(pos):
	return cards[pos].get_type()
	
func set_card_type(pos, t):
	cards[pos].set_state(t)

func _init():
	for ix in range(Global.MAXC):
		var card = CardRule.new()
		card.state = CardRule.CARD_STATE.NE
		card.type = CardRule.TYPE_UNDEFINED
		
		cards.append(card)

# generate a row of cards with a hint card
func new_row(n_level_k, n_erase, n_level_sp):
	# first decide what and where is the special card
	# there is always a special card because MAXC % 2 == 1 and MAXC % 3 == 1
	var sp_pos = randi() % Global.MAXC
	
	# find a purchased sp
	var selected_sp = randi() % n_level_sp - n_level_sp # [0, n_level_sp - 1] -> [-n_level_sp, -1]
	while (Global.user.get_owned_sp()[-selected_sp - 1] == false):
		selected_sp = randi() % n_level_sp - n_level_sp
	cards[sp_pos].set_type(selected_sp)
	
	# generate each kind has how many cards in this row
	var n_gen = Global.MAXC - 1 # minus the special card
	
	# calculate purchased card kinds
	var n_owned_k = 0
	var last_k = 0
	for ix in range(Global.MAXK):
		if (Global.user.get_owned_k()[ix]):
			n_owned_k += 1
		
		if (n_owned_k == n_level_k):
			last_k = ix
			break

	# calculate the number of cards for one kind
	# TODO: need to rethink the logic here with some randomization
	var n_per_k = []
	n_per_k.resize(last_k + 1)
	for ix in range(last_k): # last_k will be handled later
		if (Global.user.get_owned_k()[ix]):
			var n_pairs = (Global.MAXC - 1) / n_erase / n_level_k + randi() % 2 # this gives the number of pairs of one kind of cards
			while ((n_erase * n_pairs) > n_gen):
				n_pairs = (Global.MAXC - 1) / n_erase / n_level_k + randi() % 2
				
			n_per_k[ix] = n_erase * n_pairs
			n_gen -= n_per_k[ix]
		else:
			n_per_k[ix] = 0 # if no owned, set to 0

	# Assign card kinds to each position
	n_per_k[last_k] = n_gen # the remaining n_gen
	for ix in range(Global.MAXC):
		if (ix != sp_pos):
			var selected_k = randi() % (last_k + 1) + 1 # k started from 1
			while (n_per_k[selected_k - 1] <= 0):
				selected_k = randi() % (last_k + 1) + 1
				
			cards[ix].set_type(selected_k)
			
			n_per_k[selected_k - 1] -= 1

# randomly generate a row of cards
# used at the start of a game
# should follow by start()
func one_random_row(last_k, n_per_k):
	for ix in range(Global.MAXC):
		var selected_k = randi() % (last_k + 1) + 1
		while (n_per_k[selected_k - 1] <= 0):
			selected_k = randi() % (last_k + 1) + 1
			
		cards[ix].set_type(selected_k)
		
		n_per_k[selected_k - 1] -= 1

# when there is a "chaos" operation, use this random function
func shuffle(n_per_k):
	for ix in range(Global.MAXC):
		if (cards[ix].get_state() != CardRule.CARD_STATE.NE) and (!cards[ix].is_sp()):
			var selected_k = randi() % Global.MAXK + 1
			while (n_per_k[selected_k - 1] <= 0):
				selected_k = randi() % Global.MAXK + 1
				
			cards[ix].set_type(selected_k)
			
			n_per_k[selected_k - 1] -= 1
