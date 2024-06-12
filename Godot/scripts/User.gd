extends Node

class_name User

enum LOGIN_STATUS {NEW_LOGIN, WRONG_PASSWORD, SUCCESSFUL_LOGIN}

var username = ""
var password = ""

var save_file = ""

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
	
	# hash username and password for security consideration
	var username_hash = username.sha256_text()
	password_attempt = password_attempt.sha256_text()
	
	# check if save file exists
	save_file = "user://" + username_hash + ".save"
	if not FileAccess.file_exists(save_file):
		return _new_login(password_attempt)
		
	# read save file
	var file_access = FileAccess.open(save_file, FileAccess.READ)
	var json_string = file_access.get_line()
	file_access.close()
	
	var json = JSON.new()
	var error = json.parse(json_string)
	if (error):
		print("JSON Parse Error: ", json.get_error_message(), " in ", json_string, " at line ", json.get_error_line())
		get_tree().quit() # TODO
		
	var data:Dictionary = json.data
	
	# check version
	var version = data.get("version")
	if (version != Global.VERSION):
		return _new_login(password_attempt)
	
	# check password
	var password = data.get("password")
	if (password != password_attempt):
		return LOGIN_STATUS.WRONG_PASSWORD
		
	# read other data
	best_level = data.get("best_level")
	saved_level = data.get("saved_level")
	gold = data.get("gold")
	ai_forget_rate = data.get("ai_forget_rate")
	hero = data.get("hero")
	
	var owned_k_arr:Array = data.get("owned_k")
	for ix in range(owned_k_arr.size()):
		owned_k[ix] = owned_k_arr[ix]
		
	var owned_sp_arr:Array = data.get("owned_sp")
	for ix in range(owned_sp_arr.size()):
		owned_sp[ix] = owned_sp_arr[ix]
		
	return LOGIN_STATUS.SUCCESSFUL_LOGIN

func save_game():
	var data = {
		"version": Global.VERSION,
		"password": password,
		"best_level": best_level,
		"saved_level": saved_level,
		"gold": gold,
		"ai_forget_rate": ai_forget_rate,
		"hero": hero,
		"owned_k": owned_k,
		"owned_sp": owned_sp
	}
	
	var json_string = JSON.stringify(data)
	
	var file_access = FileAccess.open(save_file, FileAccess.WRITE)
	if not file_access:
		print("An error happened while saving data: ", FileAccess.get_open_error())
		return
	
	file_access.store_line(json_string)
	file_access.close()

func set_hero(ix):
	hero = ix
