extends CanvasLayer

@export var message_window_scene: PackedScene
@export var main_scene: PackedScene

var _is_successful_login = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_login_button_pressed():
	var message_window = message_window_scene.instantiate()
	message_window.hide()
	message_window.connect("ok_button_clicked", _on_ok_button_clicked)
	add_child(message_window)
	
	var username = $UsernameLineEdit.text
	var password = $PasswordLineEdit.text
	
	if username == "" or password == "":
		message_window.setup_ui("Error", "Please input valid username and password!", false)
		message_window.show()
	
		return
		
	var result = Global.user.load_game(username, password)
	
	match result:
		Global.user.LOGIN_STATUS.NEW_LOGIN:
			_is_successful_login = true
			
			message_window.setup_ui("A New Comer!", "Welcome " + username + "![p]This is your first time to the dungeon.[p]We have marked down your name on our list.[p]Hope you find your memory back!", false)
			message_window.show()
		Global.user.LOGIN_STATUS.WRONG_PASSWORD:
			message_window.setup_ui("Error", "Password wrong![p]You are not allowed to get into the dungeon!", false)
			message_window.show()
		Global.user.LOGIN_STATUS.SUCCESSFUL_LOGIN:
			_is_successful_login = true
			
			message_window.setup_ui("Welcome back!", "Welcome back to the dungeon, " + username + "!", false)
			message_window.show()
	
func _on_ok_button_clicked():
	if _is_successful_login:
		get_tree().change_scene_to_packed(main_scene)
