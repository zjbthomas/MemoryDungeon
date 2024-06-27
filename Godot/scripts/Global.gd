extends Node

const VERSION = 1

const MAXR = 6
const MAXC = 7

const MAXK = 20
const MAXSP = 6

const COST_JUMP = 5
const COST_RESET = 0
const COST_AI = 0

enum HERO_TYPE {WIZARD=0,BERSERKER=1,HUNTER=2,MASTER=3}

const WINDOW_TYPE = {
	"message": "res://scenes//MessageWindowGUI.tscn",
	"hero": "res://scenes//HeroWindowGUI.tscn",
	"collection": "res://scenes//CollectionWindowGUI.tscn",
	"shop": "res://scenes//ShopWindowGUI.tscn",
	"jump": "res://scenes//JumpWindowGUI.tscn"
}

var user = User.new()
