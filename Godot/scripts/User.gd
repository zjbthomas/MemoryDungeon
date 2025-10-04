extends Node

class_name User

enum LOGIN_STATUS {SERVER_ERROR, NEW_LOGIN, WRONG_PASSWORD, SUCCESSFUL_LOGIN}

const NEW_USER_K = 5 # initial number of normal kinds
const NEW_USER_SP = 6 # initial number of special kinds

var username = ""
var password = ""

var best_level = 0
var saved_level = 0
var gold = 0
var ai_forget_rate = 0

var owned_k = []
func set_owned_k(pos, p):
	owned_k[pos] = p
	
var owned_sp = []
func set_owned_sp(pos, p):
	owned_sp[pos] = p

var hero = Global.HERO_TYPE.WIZARD

func _init():
	owned_k.resize(Global.MAXK)
	owned_k.fill(false)
	
	owned_sp.resize(Global.MAXSP)
	owned_sp.fill(false)

# functions for connecting to Redis
const _IS_DEBUG = false
var API_BASE = ("http://localhost" if _IS_DEBUG else "https://175.178.11.87") + "/memorydungeon" # no trailing slash

func _post(url, body):
	var headers = ["Content-Type: application/json"]
	var json = JSON.stringify(body)
	var err = Global.http.request(url, headers, HTTPClient.METHOD_POST, json)
	if err != OK: return {"error":"request_failed"}
	var res = await Global.http.request_completed
	return _parse_http_result(res)

func _get(url):
	var err = Global.http.request(url, [], HTTPClient.METHOD_GET) 
	if err != OK: return {"error":"request_failed"}
	var res = await Global.http.request_completed
	return _parse_http_result(res)

func _parse_http_result(res):
	var code = res[1]
	var body = res[3]
	var text = body.get_string_from_utf8()
	if code >= 200 and code < 300:
		var parsed = JSON.parse_string(text)
		return parsed if parsed != null else {}
	return {"error": "http_%d" % code, "body": text}

func login(username, password_attempt):
	self.username = username
	self.password = password_attempt.sha256_text()

	var payload = {
		"username": username,
		"password": password
	}
	var res = await _post("%s/login" % API_BASE, payload)

	if res is Dictionary and res.has("error"):
		if (res.error == 'request_failed'):
			return LOGIN_STATUS.SERVER_ERROR
		return LOGIN_STATUS.WRONG_PASSWORD

	if res.status == "registered":
		_init_new_user()
		return LOGIN_STATUS.NEW_LOGIN
	elif res.status == "ok":
		if res.has("save") and res.save != null:
			_load(res.save)
		else:
			_init_new_user()
		return LOGIN_STATUS.SUCCESSFUL_LOGIN

	return LOGIN_STATUS.SERVER_ERROR

func save_game():
	if username == "" or password == "":
		return

	var save_dict = _build()
	var payload := {
		"username": username,
		"password": password,
		"save": save_dict
	}

	await _post("%s/save" % API_BASE, payload)

func load_game():
	if username == "" or password == "":
		return false
	var q = "?username=%s&password=%s" % [
		username.uri_encode(),
		password.uri_encode()
	]
	var res = await _get("%s/load%s" % [API_BASE, q])
	if res is Dictionary and res.has("save") and res.save != null:
		_load(res.save)
		return true
	return false

func _build():
	return {
		"version": Global.VERSION,
		"best_level": best_level,
		"saved_level": saved_level,
		"gold": gold,
		"ai_forget_rate": ai_forget_rate,
		"hero": hero,
		"owned_k": JSON.stringify(owned_k),
		"owned_sp": JSON.stringify(owned_sp),
	}

func _load(d):
	if int(d.get("version", -1)) != Global.VERSION:
		_init_new_user()
		return

	best_level = int(d.get("best_level", best_level))
	saved_level = int(d.get("saved_level", saved_level))
	gold = int(d.get("gold", gold))
	ai_forget_rate = int(d.get("ai_forget_rate", ai_forget_rate))
	hero = int(d.get("hero", hero))
	owned_k = JSON.parse_string(d.get("owned_k", owned_k))
	owned_sp = JSON.parse_string(d.get("owned_sp", owned_sp))

func _init_new_user():
	best_level = 0
	saved_level = 0
	gold = 0
	ai_forget_rate = 20
	hero = Global.HERO_TYPE.WIZARD

	for pos in range(NEW_USER_K): 
		set_owned_k(pos, true)
		
	for pos in range(NEW_USER_SP):
		set_owned_sp(pos, true)
		
	await save_game()

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
	var type = randi() % Global.MAXK

	if (owned_k[type]):
		# old card
		gold += 1 # pay back by 1
		
		save_game()
		
		return [type, false]
	else:
		# a new card
		owned_k[type] = true
		
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
