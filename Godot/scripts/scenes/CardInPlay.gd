extends AspectRatioContainer

signal card_button_clicked()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func _on_card_button_pressed():
	card_button_clicked.emit()
	
func update(card):
	var display = card.get_how_display()
	match (display):
		CardRule.CARD_STATE.NE:
			visible = false
		_:
			$Cards.play(str(display))
			visible = true
