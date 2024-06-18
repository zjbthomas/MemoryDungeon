extends Node

signal card_button_clicked(card)

var card = CardRule.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	# always cover the card at the beginning as default
	cover()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func _on_card_button_pressed():
	card_button_clicked.emit(self)
	
	# debug
	card.type = randi() % 27 - 6
	while (card.type == 0):
		card.type = randi() % 27 - 6
	if (card.state == CardRule.CARD_STATE.COVER):
		uncover()
	elif (card.state == CardRule.CARD_STATE.UNCOVER):
		cover()

func uncover():
	card.state == CardRule.CARD_STATE.UNCOVER
	$Cards.play(str(card.type))

func cover():
	card.state == CardRule.CARD_STATE.COVER
	$Cards.play("0")
