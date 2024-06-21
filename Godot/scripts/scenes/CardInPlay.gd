extends AspectRatioContainer

signal card_button_clicked(card)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func _on_card_button_pressed():
	card_button_clicked.emit(self)
	
func uncover(card):
	$Cards.play(str(card.type))

func cover():
	$Cards.play("0")
	
func update(card):
	var display = card.get_how_display()
	match (display):
		CardRule.CARD_STATE.NE:
			visible = false
		_:
			$Cards.play(str(display))
			visible = true
