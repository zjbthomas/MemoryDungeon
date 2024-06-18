extends Node

var game = GameRule.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	randomize() # call only once
	
	# some initialization for the game
	game.level = Global.user.saved_level
	game.hero = Global.user.hero
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite.play(str(Global.user.hero))

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_main_gui_next_floor_button_pressed():
	start(false)

func _on_main_gui_new_game_button_pressed():
	# TODO
	$BlurContainer/WrapperWindow.load_window("message")
	$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Error", "Please input valid username and password!", false)
	$BlurContainer.activate()

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
	# TODO: these variables are moved into GameRule
	#this->floorType = GameRule::NORMAL;
	#if (!isByConfig) {
		#this->floorType = this->game->newLevel(); // start a new level
	#}
	#this->foundTreasure = false;

	# enable progress bars
	# TODO: this->updateLevelPB();
	$MainGUI/LeftPanel/GameStatus/TopPanel/LevelBar.visible = true
	# TODO: this->updateAmPB();
	$MainGUI/LeftPanel/GameStatus/BottomPanel/AMBar.visible = true
	# TODO: this->updateHpPB();
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HPBar.visible = true

	# set right panel
	# TODO: this->updateSidebar(true);

	# hide StatusSprite and GainRect
	$MainGUI/LeftPanel/GameStatus/TopPanel/StatusSprite.visible = false
	$MainGUI/RightPanel/GameFunctions/ShopFunction/GainRect.visible = false

	# update cards
	# TODO: this->updateAllCards();

	# set controls
	$MainGUI/LeftPanel/GameControls/NextFloorButton.visible = false

	$MainGUI/LeftPanel/GameControls/NewGameButton.visible = false
	$MainGUI/LeftPanel/GameControls/PauseButton.visible = true
	$MainGUI/LeftPanel/GameControls/ResumeButton.visible = false
	
	$MainGUI/LeftPanel/GameStatus/BottomPanel/HeroSprite/HeroButton.visible = false
#
	#// setup the next level, MUST DONE AT THE END
	#ui->levelLbl->setVisible(true);
#
	#string msg = "";
	#string title = "";
#
	#switch (this->floorType) {
	#case GameRule::NORMAL:
		#ui->levelLbl->setText(QString::number(this->game->getLevel()));
#
		#msg = to_string(this->game->getOwnedKN()) + " kinds of attacks, " + to_string(this->game->getEraseN()) + " identical attacks to hit.\n" + \
					 #"Start with " + to_string(this->game->updateCurrentR()) + " rows, " + to_string(this->game->getPopN()) + " rows of reinforcement.\n" + \
					 #"Your helmet will break every " + to_string(this->game->getTimeRemain() / 10) + " seconds.\n" + \
					 #"You need to hit " + to_string(this->game->getObjective()) + " times. Good luck!";
#
		#title = "Floor " + to_string(this->game->getLevel());
#
		#ui->infoTB->setVisible(true);
		#ui->infoTB->setText(QString::fromStdString(msg));
#
		#ui->evilLbl->setVisible(false);
#
		#break;
	#case GameRule::CLOWN:
		#ui->levelLbl->setText("C");
#
		#msg = "A CLOWN FLOOR, try to survive!";
#
		#title = "CLOWN FLOOR";
#
		#ui->infoTB->setVisible(false);
#
		#ui->evilLbl->setVisible(true);
#
		#break;
	#case GameRule::EVIL:
		#ui->levelLbl->setText("E");
#
		#msg = "An EVIL FLOOR, ready to suffer...";
#
		#title = "EVIL FLOOR";
#
		#ui->infoTB->setVisible(false);
#
		#ui->evilLbl->setVisible(true);
#
		#break;
	#}
#
	#MessageDialog* messageDialog = new MessageDialog(this, msg, title, false, this->user);
	#messageDialog->setModal(true);
	#messageDialog->exec();
	#delete messageDialog;
#
	#this->amTimer->start(100);
	
	
