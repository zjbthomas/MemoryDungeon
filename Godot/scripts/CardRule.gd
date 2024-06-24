extends Node

class_name CardRule

enum CARD_STATE { # NE and COVER should be different from sp; UNCOVER can be reused
	NE=-1,
	COVER=-2,
	UNCOVER=0
} 
enum SP_TYPE { # from worst to best as evil and clown use worst types
	REINFORCE, # 0
	CHAOS,
	GOLD,
	MAP,
	HEAL,
	TREASURE
} 

const TYPE_UNDEFINED = CARD_STATE.NE
const TYPE_UNCOVER_HEAL = SP_TYPE.TREASURE + 1 # TODO: TREASURE is not a fixed value

const OFFSET = CARD_STATE.COVER - Global.MAXK # [- Global.MAXK - CardRule.CARD_STATE.COVER, CardRule.CARD_STATE.COVER - 1]

var state: CARD_STATE
var type

static func gen_random_k(last_k, n_per_k):
	var max_k = last_k + 1
	if (max_k >= Global.MAXK):
		max_k -= 1
	
	var selected_k = randi() % max_k + OFFSET
	while (n_per_k[selected_k - OFFSET] <= 0):
		selected_k = randi() % max_k + OFFSET
		
	return selected_k

func _init():
	state = CARD_STATE.NE
	type = TYPE_UNDEFINED

func is_sp():
	return type >= SP_TYPE.REINFORCE

func get_how_display():
	# make HEAL visible for MASTER
	if (is_sp() and Global.user.hero == Global.HERO_TYPE.MASTER and state != CARD_STATE.NE):
		if (type == SP_TYPE.HEAL or type == TYPE_UNCOVER_HEAL):
			state = CARD_STATE.UNCOVER
			type = TYPE_UNCOVER_HEAL
			return type
		
	if state == CARD_STATE.UNCOVER:
		return type
	else:
		return state
