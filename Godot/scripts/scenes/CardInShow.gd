extends ColorRect


# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func setup_k(ik):
	var type = ik + CardRule.OFFSET
	
	if (Global.user.owned_k[ik]):
		$VBoxContainer/CardBack/Cards.play(str(type))
		$VBoxContainer/CardBack/Cards.visible = true
	else:
		$VBoxContainer/CardBack/Cards.visible = false
		
	$VBoxContainer/RichTextLabel.text = "[center]No. " + str(ik + 1)

func setup_sp(isp):
	if (Global.user.owned_sp[isp]):
		$VBoxContainer/CardBack/Cards.play(str(isp))
		$VBoxContainer/CardBack/Cards.visible = true
	else:
		$VBoxContainer/CardBack/Cards.visible = false
		
	$VBoxContainer/RichTextLabel.text = "[center]Sp. " + str(isp + 1)
