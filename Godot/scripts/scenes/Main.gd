extends Node

# TODO： this script should work as a ViewModel; all UI operations should move to GUI

var game = GameRule.new()

const LONG_SETTLE_TIME = 0.4
const SHORT_SETTLE_TIME = 0.3
const REINFORCE_TIME = 1.2 
const CHAOS_TIME = 2
const GOLD_TIME = 0.6
const MAP_TIME = 1
const LONG_HEAL_TIME = 0.6
const SHORT_HEAL_TIME = 0.05
const TREASURE_TIME = 0.6

const AI_ACTION_TIME = 1
const AI_SETTLE_TIME = 0.3

# Called when the node enters the scene tree for the first time.
func _ready():
	randomize() # call only once

	_setup()
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _setup():
	# game status
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = false
	$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = false
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = false
	
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]" + str(Global.user.saved_level)
	
	# controls
	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = false
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	if (Global.user.saved_level != 0):
		$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = true
		
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true
	
	# user info
	$MainGUI/RightPanel/UserStatus/UsernameLabel.text = "[center][b]" + Global.user.username
	
	# update collection status
	$MainGUI/RightPanel/UserStatus/CollectionBar.visible = true
	update_collection_bar()
	
	$MainGUI/RightPanel/UserStatus/BestLabel.text = "[center]" + str(Global.user.best_level)
	$MainGUI/RightPanel/UserStatus/SavedLabel.text = "[center]" + str(Global.user.saved_level)
	
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.visible = true
	
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
	
	# floor info
	$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]Come on to a new floor!"
	$MainGUI/RightPanel/FloorInfo/EvilRect.visible = false
	
	# init game and hero
	game.level = Global.user.saved_level
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))

func _on_main_gui_next_floor_button_pressed():
	start(false)

# TODO: new_game_button should only be available after game over
func _on_main_gui_new_game_button_pressed():
	game.level = Global.user.saved_level
	start(false)

func _on_main_gui_pause_button_pressed():
	if ($SettleTimer.is_stopped()):
		$AMTimer.stop()
		
	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = true
	
	$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
	
	update_function_controls(false)

func _on_main_gui_resume_button_pressed():
	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = false
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = true
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	update_function_controls(true)
	
	$AMTimer.start()

# for hero system
func _on_main_gui_hero_button_pressed():
	$BlurContainer/WrapperWindow.load_window("hero")
	$BlurContainer/WrapperWindow.get_loaded_window().hero_selected.connect(_on_hero_selected)
	$BlurContainer.activate()
	
func _on_hero_selected(ix):
	$BlurContainer.complete()
	
	Global.user.hero = ix
	Global.user.save_game()
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))

func _on_main_gui_collection_button_pressed():
	$BlurContainer/WrapperWindow.load_window("collection")
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
	$BlurContainer.activate()

func _on_main_gui_shop_button_pressed():
	$BlurContainer/WrapperWindow.load_window("shop")
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_shop_ok_button_pressed)
	$BlurContainer.activate()

func _on_main_gui_jump_button_pressed():
	# minus credit, write to the user file and refresh to show
	Global.user.gold -= Global.COST_JUMP
	Global.user.save_game()
	
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
	
	update_function_controls(false)
	
	# show message
	var msg = "You pay " + str(Global.COST_JUMP) + " credits to buy the items.[p]" + \
					"Ready to choose the next floor!"
	
	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Jumping", msg, false)
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_jump_msg_ok_button_pressed)
	$BlurContainer.activate()
	
func _on_jump_msg_ok_button_pressed():
	$BlurContainer.complete()
	
	# show jump form
	$BlurContainer/WrapperWindow.load_window("jump")
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_jump_ok_button_pressed)
	$BlurContainer.activate()

func _on_jump_ok_button_pressed(n_erase, n_level_k, n_rows, n_pop):
	$BlurContainer.complete()
	
	# set and start a new level
	game.level = Global.user.saved_level
	
	game.new_level_by_config(n_erase, n_level_k, n_rows, n_pop)

	start(true)

func _on_main_gui_reset_button_pressed():
	# convert saved level to gold
	var gain_gold = int(Global.user.saved_level / 3) # TODO: magic number here
	
	Global.user.saved_level = 0
	Global.user.gold + gain_gold
	Global.user.save_game()
	
	game.level = 0
	
	# update UI
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = Global.user.gold
	
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]0"
	$MainGUI/RightPanel/UserStatus/SavedLabel.text = "[center]0"

	# acts like game over
	# stop timing
	$AMTimer.stop()
	$SettleTimer.stop()
	
	# update UI
	$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
	
	update_function_controls(false)
	
	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = false
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true
	
	# show message
	var msg = "Welcome back to your hometown![p]" + \
					"Your conquests give you "+ str(gain_gold) + " golds.[p]" + \
					"Ready to fight again!"
	
	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Welcome home!", msg, false)
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
	$BlurContainer.activate()

func _on_shop_ok_button_pressed():
	$BlurContainer.complete()
	update_collection_bar()

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

	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.visible = true

	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui(title, msg, false)
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_start_ok_button_pressed)
	$BlurContainer.activate()
	
func _on_start_ok_button_pressed():
	$BlurContainer.complete()
	$AMTimer.start()

func update_level_bar():
	# TODO: we mix changing colors of the progress bar and setting its value together; should be separated
	if (game.is_in_ai_mode == false):
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

func update_collection_bar():
	$MainGUI/RightPanel/UserStatus/CollectionBar.min_value = 0
	$MainGUI/RightPanel/UserStatus/CollectionBar.max_value = 100
	$MainGUI/RightPanel/UserStatus/CollectionBar.value = Global.user.get_collection_rate()

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
	$MainGUI/Board.update_one_card(ir, ic, game.get_card_for_ui(ir, ic))

func _on_board_card_button_pressed(ir, ic):
	if (game.is_in_ai_mode == false):
		if (!$AMTimer.is_stopped() and $SettleTimer.is_stopped() and game.is_card_clickable_from_ui(ir, ic)):
			# game is running and not in settle phase
			# hide status
			$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
			
			$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
			
			match (game.perform_click_from_ui(ir, ic)):
				GameRule.CLICK_PERFORMED.NO_SETTLEMENT:
					update_one_card(ir, ic)
				GameRule.CLICK_PERFORMED.SETTLEMENT:
					match (game.n_erase):
						2:
							$SettleTimer.wait_time = LONG_SETTLE_TIME
						3:
							$SettleTimer.wait_time = SHORT_SETTLE_TIME
					
					update_one_card(ir, ic)
					
					$SettleTimer.start()
				CardRule.SP_TYPE.REINFORCE:
					# for HUNTER
					if (Global.user.hero == Global.HERO_TYPE.HUNTER):
						$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
						update_function_controls(true) # update as gold changed
						
					# update all cards as REINFORCE shows all cards
					update_all_cards()
					
					$SettleTimer.wait_time = REINFORCE_TIME
					$SettleTimer.start()
				CardRule.SP_TYPE.CHAOS:
					# for HUNTER
					if (Global.user.hero == Global.HERO_TYPE.HUNTER):
						$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
						update_function_controls(true) # update as gold changed
					
					# update all cards as CHAOS shows all cards
					update_all_cards()
					
					$SettleTimer.wait_time = CHAOS_TIME
					$SettleTimer.start()
				CardRule.SP_TYPE.GOLD:
					$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
					update_function_controls(true) # update as gold changed
					
					$SettleTimer.wait_time = GOLD_TIME
					$SettleTimer.start()
					
					update_one_card(ir, ic)
				CardRule.SP_TYPE.MAP:
					$SettleTimer.wait_time = MAP_TIME
					$SettleTimer.start()
					
					# TODO: the cards to recover are dynamically found; update_all_cards() is safe, but not efficient
					update_all_cards()
				CardRule.SP_TYPE.HEAL, CardRule.TYPE_UNCOVER_HEAL:
					update_am_bar()
					
					if (Global.user.hero != Global.HERO_TYPE.MASTER):
						$SettleTimer.wait_time = LONG_HEAL_TIME
					else:
						$SettleTimer.wait_time = SHORT_HEAL_TIME # TODO: as HEAL is visible to MASTER, the display time is shorter; can we directly call settle()?
					
					update_one_card(ir, ic)
					
					$SettleTimer.start()
				CardRule.SP_TYPE.TREASURE:
					# for HUNTER
					if (Global.user.hero == Global.HERO_TYPE.HUNTER):
						$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
						update_function_controls(true) # update as gold changed

					$SettleTimer.wait_time = TREASURE_TIME
					
					update_one_card(ir, ic)
					
					$SettleTimer.start()
			
			update_hp_bar() # TODO: it is better to make it run before SettleTimer.start()
	else:
		# AI mode
		# TODO: is this logic correct?
		if ($AITimer.is_stopped() and game.is_card_clickable_from_ui(ir, ic)):
			#update_one_card(ir, ic)
			
			if (game.get_card_for_ui(ir, ic).state == CardRule.CARD_STATE.COVER):
				# hide status
				$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
				
				$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
				
				var click_performed = game.perform_click_from_ui(ir, ic)
				
				update_one_card(ir, ic)	
				
				if (click_performed == GameRule.CLICK_PERFORMED.SETTLEMENT):
					$AITimer.wait_time = AI_SETTLE_TIME
					$AITimer.start()

func _on_settle_timer_timeout():
	# call settle()
	game.settle()
	
	# update status
	if (game.status == GameRule.STATUS.EMPTY):
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	elif (game.status <= GameRule.STATUS.CRITICAL):
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.play(str(game.status))
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = true
	elif (game.status == GameRule.STATUS.CREDIT):
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.play(str(GameRule.STATUS.BONUS))
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = true
		
		$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = true
		
	# update progress bar for level
	update_level_bar()
	
	# update all cards
	update_all_cards()

	# TODO: win game logic; should move to a separate function
	if (game.win_game):
		$AMTimer.stop()
		
		# update UI
		# hide progress bars
		$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = false
		$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = false
		$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = false

		# hide status
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
		$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
		
		update_all_cards()
		
		# set controls
		$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
		$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
		$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true
		
		# handle TREASURE
		if (game.found_treasure):
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Wow!", "You find a gift in this floor![p]Please receive it!", true)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_found_treasure_ok_button_clicked)
			$BlurContainer.activate()
		else:
			_settle_check_floor_type()

func _on_found_treasure_ok_button_clicked():
	$BlurContainer.complete()
	_settle_check_floor_type()
	
func _settle_check_floor_type():
	# add gold and gift
	# TODO: all magic numbers here!
	match (game.floor_type):
		GameRule.FLOOR_TYPE.NORMAL:
			Global.user.gold += 1
			_settle_update_ui()
		GameRule.FLOOR_TYPE.CLOWN:
			Global.user.gold += 3
			_settle_update_ui()
		GameRule.FLOOR_TYPE.EVIL:
			Global.user.gold += 5
			
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Wow!", "You get the chest from beating EVIL![p]Let's open it!", true)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): _on_evil_gift_ok_button_pressed)
			$BlurContainer.activate()

func _on_evil_gift_ok_button_pressed():
	$BlurContainer.complete()
	_settle_update_ui()

func _settle_update_ui():
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)

	# update function controls here as gold value changed
	update_function_controls(false)
	
	# update collection bar as gift provided
	update_collection_bar()

	# update saved level
	Global.user.saved_level = game.level
	
	$MainGUI/RightPanel/UserStatus/SavedLabel.text = "[center]" + str(Global.user.saved_level)
	
	# update best level
	if (game.level > Global.user.best_level):
		Global.user.best_level = game.level
		
		$MainGUI/RightPanel/UserStatus/BestLabel.text = "[center]" + str(Global.user.best_level)

	# save game
	Global.user.save_game()

	# show the button to the next floor
	$MainGUI/RightPanel/FloorInfo/EvilRect.visible = false
	$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]Well done![p]Let's go to the next floor!"
	
	$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = true

func _on_am_timer_timeout():
	if (game.time_remain > 0):
		game.time_remain -= 1
		update_am_bar()
	else:
		# helmet break
		if ($SettleTimer.is_stopped()):
			var survive = game.pop_rows(game.n_pop)
			
			if (survive):
				# a new row is popped, update all cards
				update_all_cards()
				
				# progress bars changed
				update_level_bar()
				update_hp_bar()
				
				# reset status
				$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
				$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
				
				update_am_bar() # TODO: does the order matter here?
			else:
				# game over
				# stop timing
				$AMTimer.stop()
				$SettleTimer.stop()
			
				# reset everything
				# TODO: can we put it into a function as RESET?
				
				# reset user level to 0
				Global.user.saved_level = 0
				
				update_all_cards()
				
				$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]0"
				
				$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = false
				
				$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = false
				$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = false
				
				$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
				$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
				
				update_function_controls(false)
	
				$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
				$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
				$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
				
				$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true

				# message for game over
				$BlurContainer/WrapperWindow.load_window("message")
				$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Gameover", "Time's Up![p]Gameover.", false)
				$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
				$BlurContainer.activate()

func _on_main_gui_ai_button_pressed():
	var ai_remember_rate = 100 - Global.user.ai_forget_rate # TODO: why not directly use remember rate?
	
	game.new_ai_level(ai_remember_rate)
	
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]U"
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.visible = true
	
	# set progress bars
	update_level_bar()
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = true
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = false
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = false

	# set right panel
	update_function_controls(false)

	# update cards
	update_all_cards()
	
	# set controls
	$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = false

	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = false
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true # TODO: why?

	# show message
	var msg = "Ready to fight your master![p]" + \
			  "The forget percentage of your master is " + str(ai_remember_rate)+ "%!"

	$MainGUI/RightPanel/FloorInfo/MessageLabel.visible = true
	$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]" + msg

	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Get set!", msg, false)
	$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
	$BlurContainer.activate()


func _on_ai_timer_timeout():
	$AITimer.stop() # TODO: this may not be needed
	
	var start_ai_timer = false
	
	if (!game.is_ai_turn):
		game.settle_ai() # this will change is_ai_turn
	
		if (game.status == GameRule.STATUS.SCORE):
			update_level_bar()
			
			$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.play(str(game.status))
			$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = true

		update_all_cards()
		
		# change to AI's turn
		if (game.is_ai_turn):
			$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]M"
			
			$MainGUI/LeftPanel/GameControls/NewGameButton.visible = false
			
			update_function_controls(true)

			start_ai_timer = true

	else:
		# AI's turn
		match game.perform_ai_action():
			0: # this is actually reset from 3, which means we need to settle
				game.settle_ai()
				
				if (game.status == GameRule.STATUS.AISCORE):
					update_level_bar()
					
					$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.play(str(GameRule.STATUS.BREAK))
					$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = true
				
				# change to player's turn
				if (!game.is_ai_turn):
					$MainGUI/LeftPanel/GameStatus/TopPanel/LevelLabel.text = "[center][b]U"
					
					$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
					
					update_function_controls(true)

			1, 2: # AI continues its action
				start_ai_timer = true
				
		update_all_cards()
		
		# TODO: seems like this should be put into case 0 above
		if (game.is_ai_turn):
			start_ai_timer = true

	if (game.win_game):
		# stop AI timer in case the previous if statement activate it
		# TODO: check the logic here; do we just reset the flag without stop the timer?
		$AITimer.stop()
		start_ai_timer = false
		
		# reset UI
		$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = false
		
		$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
		$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false
		
		update_function_controls(false)
		
		update_all_cards()
		
		# show message
		if (game.score == game.ai_score):
			var msg = "You get the same score as your master.[p]Please start another training!"
			
			$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]" + msg
			
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Draw", msg, false)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
			$BlurContainer.activate()
		elif (game.score > game.ai_score):
			var gain_gold = Global.user.handle_ai_end_game(game.score, game.ai_score)
			
			$MainGUI/RightPanel/GameFunctions/ShopFunction/GoldLabel.text = str(Global.user.gold)
			update_function_controls(false) # update as gold changed
			
			var msg = "Congratulations! You win your master![p]" + \
					  "You have earn "+ str(gain_gold) + " credits![p]" + \
					  "Please start a new training to win more!"
			
			$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]" + msg
			
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Win", msg, false)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
			$BlurContainer.activate()
		elif (game.score < game.ai_score):
			Global.user.handle_ai_end_game(game.score, game.ai_score)
			
			var msg = "Sorry you lose this time![p]" + \
					  "Please start a new training and try again!";
			
			$MainGUI/RightPanel/FloorInfo/MessageLabel.text = "[b]" + msg
			
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Win", msg, false)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(func(): $BlurContainer.complete())
			$BlurContainer.activate()
			
		$MainGUI/LeftPanel/GameControls/NewGameButton.visible = true
		$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = true

	if (start_ai_timer):
		$AITimer.wait_time = AI_ACTION_TIME # TODO: this timer is reused for two different purposes; shall we use two timers?
		$AITimer.start()
