extends TextureRect

signal ok_button_pressed

var _price = 10 # TODO: magic number here
var _is_new_type = false

var _is_in_animation = false

# Called when the node enters the scene tree for the first time.
func _ready():
	_update_ui()
	
	$InfoLabel.text = "Have a try to find your memory!"
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _update_ui():
	$GoldLabel.text = "[center][b]" + str(Global.user.gold) + "G"
	$PriceLabel.text = "[center]" + str(max(_price, 0)) + "G"

#func _check_drawable():
	#if (Global.user.gold >= _price):
		#get_tree().call_group("draw_cards", "set_button", true)
	#else:
		#get_tree().call_group("draw_cards", "set_button", false)

func _on_card_in_draw_card_button_pressed(card):
	if (!_is_in_animation):
		if (Global.user.gold >= _price):
			var rets = Global.user.gacha(_price) # the gold is decreased inside this function
			var type = rets[0]
			_is_new_type = rets[1]
			
			$OKButton.disabled = true
			_is_in_animation = true # do not allow other cards to be clicked
			
			$InfoLabel.text = "Finding..."
			
			SoundEffect.play("card_draw")
			
			card.card_flip(type)
		else:
			$InfoLabel.text = "Not enough gold!"

func _on_card_in_draw_card_flipped():
	if (_is_new_type):
		$InfoLabel.text = "You find part of your memory!"
		
		SoundEffect.play("lucky_draw")
	else:
		$InfoLabel.text = "Sorry, you are not lucky enough this time."
		
		SoundEffect.play("unlucky_draw")

	# update price
	_price -= 1
	_update_ui()
	
	_is_in_animation = false # allow other cards to be clicked
	$OKButton.disabled = false

func _on_ok_button_pressed():
	if (!_is_in_animation):
		# first, check if there is a free gift
		if (_price <= 0):
			# TODO: magic number here
			var msg = "Thanks for drawing 10 times![p]" + \
					   "You get a free gift![p]" + \
						"Please receive it!"
			
			$BlurContainer/WrapperWindow.load_window("message")
			$BlurContainer/WrapperWindow.get_loaded_window().setup_ui("Wow!", msg, true)
			$BlurContainer/WrapperWindow.get_loaded_window().ok_button_pressed.connect(_on_gift_ok_button_pressed)
			$BlurContainer.activate()
		else:
			ok_button_pressed.emit()

func _on_gift_ok_button_pressed():
	$BlurContainer.complete()
	ok_button_pressed.emit()
			
