extends TextureRect

signal ok_button_pressed

var _is_new_type:bool = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func setup_ui(title, message, is_gift):
	$TitleLabel.text = "[center][b]" + title
	$MessageLabel.text = "[b]" + message
	
	if (!is_gift):
		$ImageContainer/DefaultImage.visible = true
		$ImageContainer/CardInDraw.visible = false
		
		$OKButton.disabled = false
	else:
		$ImageContainer/DefaultImage.visible = false
		$ImageContainer/CardInDraw.visible = true
		
		$OKButton.disabled = true

func _on_ok_button_pressed():
	ok_button_pressed.emit()

func _on_card_in_draw_card_button_pressed(card):
	var rets = Global.user.gacha(0)
	var type = rets[0]
	_is_new_type = rets[1]
	
	SoundEffect.play("card_draw")
	
	card.card_flip(type)

func _on_card_in_draw_card_flipped():
	if (_is_new_type):
		$MessageLabel.text = "[b]You find part of your memory!"
		
		SoundEffect.play("lucky_draw")
	else:
		$MessageLabel.text = "[b]Sorry, you are not lucky enough this time."
		
		SoundEffect.play("unlucky_draw")
	
	$OKButton.disabled = false
