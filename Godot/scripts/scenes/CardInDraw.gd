extends Sprite2D

signal card_flipped

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func setup_card(card_type):
	$Cards.play(str(card_type))

func _on_card_button_pressed():
	card_flip()
	$CardButton.visible = false # animation can only played once
	
func card_flip():
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
