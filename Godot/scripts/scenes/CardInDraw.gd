extends Sprite2D

signal card_button_pressed(card)
signal card_flipped

var _is_drawn:bool = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_card_button_pressed():
	card_button_pressed.emit(self)

func card_flip(card_type):
	$Cards.play(str(card_type + CardRule.OFFSET))
	
	# animation can only played once
	_is_drawn = true
	$CardButton.visible = false 
	
	var ori_scale_x = self.scale.x
	
	var tween = get_tree().create_tween().bind_node(self)
	tween.tween_property(self, "scale:x", 0.1, 0.1)
	tween.tween_property(self, "scale:x", ori_scale_x, 0.1)
	tween.tween_property(self, "scale:x", 0.1, 0.2)
	tween.tween_property(self, "scale:x", ori_scale_x, 0.2)
	tween.tween_property(self, "scale:x", 0.1, 0.4)
	tween.tween_property(self, "scale:x", ori_scale_x, 0.4)
	
	tween.parallel().tween_property($Cards, "z_index", 0, 0.05).set_trans(Tween.TRANS_CUBIC)

	tween.tween_callback(func(): card_flipped.emit())

func set_button(b):
	if (_is_drawn):
		$CardButton.visible = false
	else:
		$CardButton.visible = b
