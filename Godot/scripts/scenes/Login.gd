extends TextureRect

@export var main_scene: PackedScene

var _is_successful_login = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_login_button_pressed():
	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().connect("ok_button_pressed", _on_ok_button_pressed)
	
	var username = $UsernameLineEdit.text
	var password = $PasswordLineEdit.text
	
	if username == "" or password == "":
		$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Error", "Please input valid username and password!", false)
		$BlurContainer.activate()
	
		return
		
	var result = Global.user.load_game(username, password)
	
	match result:
		Global.user.LOGIN_STATUS.NEW_LOGIN:
			_is_successful_login = true
			
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("A New Comer!", "Welcome " + username + "![p]This is your first time to the dungeon.[p]We have marked down your name on our list.[p]Hope you find your memory back!", false)
			$BlurContainer.activate()
		Global.user.LOGIN_STATUS.WRONG_PASSWORD:
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Error", "Password wrong![p]You are not allowed to get into the dungeon!", false)
			$BlurContainer.activate()
		Global.user.LOGIN_STATUS.SUCCESSFUL_LOGIN:
			_is_successful_login = true
			
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Welcome back!", "Welcome back to the dungeon, " + username + "!", false)
			$BlurContainer.activate()

func _on_ok_button_pressed():
	$BlurContainer.complete()
	
	if _is_successful_login:
		get_tree().change_scene_to_packed(main_scene)
