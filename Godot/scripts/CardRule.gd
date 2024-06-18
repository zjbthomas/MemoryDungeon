extends Node

class_name CardRule

const TYPE_UNDEFINED = 0

enum CARD_STATE {NE=-1, COVER=0, UNCOVER=1} # NE and COVER should be different from sp
enum SP_TYPE {REINFORCE=-1, CHAOS=-2, GOLD=-3, MAP=-4, HEAL=-5, TREASURE=-6} # from worst to best as evil and clown use worst types

var state:CARD_STATE
var type # 0 for not defined, 1 or more for normal kinds.

var r
var c

func is_sp():
	return type <= 0
