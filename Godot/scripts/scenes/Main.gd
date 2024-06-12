extends Node


# Called when the node enters the scene tree for the first time.
func _ready():
	pass


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_gui_hero_button_pressed():
	$WrapperWindow.load_window("hero")
	$WrapperWindow.get_loaded_window().connect("hero_selected", _on_hero_selected)
	$WrapperWindow.popup_centered()
	
func _on_hero_selected(ix):
	$WrapperWindow.completed()
	
	Global.user.set_hero(ix)
	Global.user.save_game()
	
	# TODO: change hero avatar
