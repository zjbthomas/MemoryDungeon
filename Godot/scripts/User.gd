extends Node

class_name User

enum LOGIN_STATUS {NEW_LOGIN, WRONG_PASSWORD, SUCCESSFUL_LOGIN}

const NEW_USER_K = 5 # initial number of normal kinds
const NEW_USER_SP = 6 # initial number of special kinds

var username = ""
var password = ""

var save_file = ""

var best_level = 0
var saved_level = 0
var gold = 0
var ai_forget_rate = 20

var owned_k = []
func set_owned_k(pos, p):
	owned_k[pos] = p
	
var owned_sp = []
func set_owned_sp(pos, p):
	owned_sp[pos] = p

var hero = Global.HERO_TYPE.MASTER

func _init():
	owned_k.resize(Global.MAXK)
	owned_k.fill(false)
	
	owned_sp.resize(Global.MAXSP)
	owned_sp.fill(false)

func _new_login(password_attempt):
	self.password = password_attempt
	
	# setup new user
	for pos in range(NEW_USER_K): 
		set_owned_k(pos, true)
		
	for pos in range(NEW_USER_SP):
		set_owned_sp(pos, true)
	
	# save new user profile
	save_game()
	
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
	else:
		self.password = password
	
	# read other data
	best_level = data.get("best_level")
	saved_level = data.get("saved_level")
	gold = data.get("gold")
	ai_forget_rate = data.get("ai_forget_rate")
	hero = data.get("hero")
	owned_k = data.get("owned_k")
	owned_sp = data.get("owned_sp")

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

func cal_last_k(n_level_k):
	var n_owned_k = 0
	var last_k = 0
	for ix in range(Global.MAXK):
		if (owned_k[ix]):
			n_owned_k += 1
		
		if (n_owned_k == n_level_k):
			last_k = ix
			break
			
	return last_k

func gacha(cost):
	# first substract the credit
	gold -= cost

	# generate a random card.
	var type = randi() % Global.MAXK + 1

	if (owned_k[type - 1]):
		# old card
		gold += 1 # pay back by 1
		
		save_game()
		
		return [type, false]
	else:
		# a new card
		owned_k[type - 1] = true
		
		save_game()
		
		return [type, true]

func get_collection_rate():
	return int(100 * (owned_k.count(true) + owned_sp.count(true)) / (Global.MAXK + Global.MAXSP))

# save_game() is automatically called in this function
func handle_ai_end_game(score, ai_score):
	var gain_gold:int = (score - ai_score) / 4 + 1
	if (gain_gold > 0):
		gold += gain_gold
#
	# ajust AI remember percentage
	var adjustment = score - ai_score
	
	ai_forget_rate = clamp(ai_forget_rate + adjustment, 0, 100)

	save_game()
	
	return gain_gold
