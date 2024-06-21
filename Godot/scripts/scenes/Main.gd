extends Node

var game = GameRule.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	randomize() # call only once
	
	# some initialization for the game
	game.level = Global.user.saved_level
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_main_gui_next_floor_button_pressed():
	start(false)

func _on_main_gui_new_game_button_pressed():
	pass

# for hero system
func _on_main_gui_hero_button_pressed():
	$BlurContainer/WrapperWindow.load_window("hero")
	$BlurContainer/WrapperWindow.get_loaded_window().connect("hero_selected", _on_hero_selected)
	$BlurContainer.activate()
	
func _on_hero_selected(ix):
	$BlurContainer.complete()
	
	Global.user.hero = ix
	Global.user.save_game()
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))

func start(is_by_config):
	if (not is_by_config):
		game.new_level() # start a new level

	# enable progress bars
	update_level_bar()
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = true
	update_am_bar()
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = true
	update_hp_bar()
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = true

	# set right panel
	update_function_controls(true)

	# hide StatusSprite and GainRect
	$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false

	# update cards
	update_all_cards()

	# set controls
	$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = false

	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = false
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = true
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = false
#
	# in the following, we setup the message box and UI based on floor_type
	var title = ""
	var msg = ""
	
	match (game.floor_type):
		GameRule.FLOOR_TYPE.NORMAL:
			title = "Floor " + str(game.level)
			msg = str(Global.user.owned_k.count(true)) + " kinds of attacks, " + str(game.n_erase) + " identical attacks to hit.[p]" + \
					"Start with " + str(game.update_cur_n_rows()) + " rows, " + str(game.n_pop) + " rows of reinforcement.[p]" + \
					 "Your helmet will break every " + str(game.time_remain) + " seconds.[p]" + \
					 "You need to hit " + str(game.objective) + " times. Good luck!"
					
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]" + str(game.level)
#
			$MainGUI/RightPanel/FloorInfo/MessageLabel.visible = true
			$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]" + msg
			
			$MainGUI/RightPanel/FloorInfo/EvilRect.visible = false
#
		GameRule.FLOOR_TYPE.CLOWN:
			title = "CLOWN FLOOR"
			msg = "A CLOWN FLOOR, try to survive!"
			
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]C"
#
			$MainGUI/RightPanel/FloorInfo/MessageLabel.visible = false

			$MainGUI/RightPanel/FloorInfo/EvilRect.visible = true
		
		GameRule.FLOOR_TYPE.EVIL:
			title = "EVIL FLOOR"
			msg = "An EVIL FLOOR, ready to suffer..."
			
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]E"
#
			$MainGUI/RightPanel/FloorInfo/MessageLabel.visible = false

			$MainGUI/RightPanel/FloorInfo/EvilRect.visible = true

	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui(title, msg, false)
	$BlurContainer/WrapperWindow.get_loaded_window().connect("ok_button_pressed", func(): $BlurContainer.complete())
	$BlurContainer.activate()
#
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.visible = true
	
	#TODO: this->amTimer->start(100);
	
func update_level_bar():
	# TODO: we mix changing colors of the progress bar and setting its value together; should be separated
	if (game.is_ai_turn == false):
		if (game.floor_type == GameRule.FLOOR_TYPE.NORMAL):
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("background").bg_color = Color.BLACK
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("fill").bg_color = Color.YELLOW
			
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.min_value = 0
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.max_value = game.objective
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.value = game.score
		else:
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("background").bg_color = Color.BLACK
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("fill").bg_color = Color.RED
			
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.min_value = 0
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.max_value = game.objective
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.value = game.objective - game.score # reversed value
	else:
		$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("background").bg_color = Color.RED
		$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.get_theme_stylebox("fill").bg_color = Color.BLUE
		
		$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.min_value = 0
		if (game.score + game.ai_score == 0):
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.max_value = 2
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.value = 1
		else:
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.max_value = game.score + game.ai_score
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.value = game.score

func update_am_bar():
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.min_value = 0
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.max_value = game.base_time
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.value = game.time_remain

func update_hp_bar():
	# TODO: we mix changing colors of the progress bar and setting hero avatar together; should be separated
	if (game.update_cur_n_rows() + game.n_pop > Global.MAXR):
		$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero) + "_d")
	else:
		$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))
		
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.min_value = 0
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.max_value = Global.MAXR
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.value = Global.MAXR - (game.update_cur_n_rows() - 1) # TODO: do we need to call update_cur_n_rows or just use cur_n_rows?

# TODO: we should set a flag call is_processing; group all operations into two functions when is_processing is set and clear
func update_function_controls(is_processing):
	$MainGUI/RightPanel/GameFunctions/ShopFunction/ShopButton.visible = !is_processing
	$MainGUI/RightPanel/GameFunctions/JumpFunction/JumpButton.visible = !is_processing and (Global.user.gold >= Global.COST_JUMP)
	$MainGUI/RightPanel/GameFunctions/ResetFunction/ResetButton.visible = !is_processing and (Global.user.gold >= Global.COST_RESET)
	$MainGUI/RightPanel/GameFunctions/AIFunction/AIButton.visible = !is_processing and (Global.user.gold >= Global.COST_AI)

func update_all_cards():
	for ir in range(Global.MAXR):
		for ic in range(Global.MAXC):
			update_one_card(ir, ic)
			
func update_one_card(ir, ic):
	$MainGUI/Board.update_one_card(ir, ic, game.rows[ir].cards[ic])
