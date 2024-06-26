extends TextureRect

signal next_floor_button_pressed
signal new_game_button_pressed
signal pause_button_pressed
signal resume_button_pressed

signal hero_button_pressed

signal collection_button_pressed
signal shop_button_pressed

signal ai_button_pressed

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
	
func _on_pause_button_pressed():
	pause_button_pressed.emit()

func _on_resume_button_pressed():
	resume_button_pressed.emit()

func _on_hero_button_pressed():
	hero_button_pressed.emit()

func _on_collection_button_pressed():
	collection_button_pressed.emit()

func _on_shop_button_pressed():
	shop_button_pressed.emit()

func _on_ai_button_pressed():
	ai_button_pressed.emit()

func _on_exit_button_pressed():
	get_tree().quit()


