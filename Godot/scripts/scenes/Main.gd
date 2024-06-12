extends Node

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_main_gui_hero_button_pressed():
	$BlurContainer/WrapperWindow.load_window("hero")
	$BlurContainer/WrapperWindow.get_loaded_window().connect("hero_selected", _on_hero_selected)
	$BlurContainer.activate()
	
func _on_hero_selected(ix):
	$BlurContainer.complete()
	
	Global.user.set_hero(ix)
	Global.user.save_game()
	
	# TODO: change hero avatar


func _on_main_gui_new_game_button_pressed():
	# TODO
	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Error", "Please input valid username and password!", false)
	$BlurContainer.activate()
