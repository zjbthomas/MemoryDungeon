extends TextureRect

signal next_floor_button_pressed
signal new_game_button_pressed
signal hero_button_pressed

# Called when the node enters the scene tree for the first time.
func _ready():
	setup_ui()

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

func setup_ui():
	# game status
	$LeftPanel/GameStatus/TopPanel/LevelBar.visible = false
	$LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	
	$LeftPanel/GameStatus/BottomPanel/AMBar.visible = false
	$LeftPanel/GameStatus/BottomPanel/HPBar.visible = false
	
	if (Global.user.saved_level != 0):
		$LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]" + str(Global.user.saved_level)
	else:
		$LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]0"
	
	# controls
	$LeftPanel/GameControls/NewGameButton.visible = false
	$LeftPanel/GameControls/PauseButton.visible = false
	$LeftPanel/GameControls/ResumeButton.visible = false
	
	if (Global.user.saved_level != 0):
		$LeftPanel/GameControls/NextFloorButton.visible = true
		
	$LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true
	
	# user info
	$RightPanel/UserStatus/UsernameLabel.text = "[center][b]" + Global.user.username
	
	# TODO: update collection status
	$RightPanel/UserStatus/CollectionBar.visible = true
	
	$RightPanel/UserStatus/BestLabel.text = "[center]" + str(Global.user.best_level)
	$RightPanel/UserStatus/SavedLabel.text = "[center]" + str(Global.user.saved_level)
	
	$RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
	$RightPanel/GameFunctions/ShopFunction/GoldLabel.visible = true
	
	$RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
	
	# floor info
	$RightPanel/FloorInfo/MessageLabel.text = "[b]Come on to a new floor!"
	$RightPanel/FloorInfo/EvilRect.visible = false
	
	
	
	
	
	
	
	
	



