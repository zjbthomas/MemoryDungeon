extends TextureRect

signal next_floor_button_pressed
signal new_game_button_pressed
signal hero_button_pressed

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_next_floor_button_pressed():
	next_floor_button_pressed.emit()

func _on_new_game_button_pressed():
	new_game_button_pressed.emit()
	
func _on_hero_button_pressed():
	hero_button_pressed.emit()

func _on_exit_button_pressed():
	get_tree().quit()
	
	
	
	
	
	
	
	
	



