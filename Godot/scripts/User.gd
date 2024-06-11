extends Node

class_name User

const SAVE_FILE = "user://savegame.save"
enum LOGIN_STATUS {NEW_LOGIN, WRONG_PASSWORD, SUCCESSFUL_LOGIN}

var username = ""
var password = ""

var best_level = 0
var saved_level = 0
var gold = 0
var ai_forget_rate = 20

var owned_k = []
var owned_sp = []

var hero = 0

func _init():
	owned_k.resize(Global.MAXK)
	owned_k.fill(false)
	
	owned_sp.resize(Global.MAXSP)
	owned_sp.fill(false)

func _new_login(password_attempt):
	self.password = password_attempt
	return LOGIN_STATUS.NEW_LOGIN

func load_game(username, password_attempt):
	self.username = username
	
	# check if save file exists
	if not FileAccess.file_exists(SAVE_FILE):
		return _new_login(password_attempt)
		
	# read save file
	var file_access = FileAccess.open(SAVE_FILE, FileAccess.READ)
	var json_string = file_access.get_line()
	file_access.close()
	
	var json = JSON.new()
	var error = json.parse(json_string)
	if (error):
		get_tree().quit() # TODO
		
	var data:Dictionary = json.data
	
	# check if username exists in save file
	if !data.has(username):
		self.password = password_attempt
		return _new_login(password_attempt)
	
	var user_data:Dictionary = data.get(username)
	
	# check version
	var version = user_data.get("version")
	if (version != Global.VERSION):
		return _new_login(password_attempt)
	
	# check password
	var password = user_data.get("password")
	if (password != password_attempt):
		return LOGIN_STATUS.WRONG_PASSWORD
		
	# read other data
	best_level = user_data.get("best_level")
	saved_level = user_data.get("saved_level")
	gold = user_data.get("gold")
	ai_forget_rate = user_data.get("ai_forget_rate")
	hero = user_data.get("hero")
	
	var owned_k_arr:Array = user_data.get("owned_k")
	for ix in range(owned_k_arr.size()):
		owned_k[ix] = owned_k_arr[ix]
		
	var owned_sp_arr:Array = user_data.get("owned_sp")
	for ix in range(owned_sp_arr.size()):
		owned_sp[ix] = owned_sp_arr[ix]
		
	return LOGIN_STATUS.SUCCESSFUL_LOGIN
		
	
	
