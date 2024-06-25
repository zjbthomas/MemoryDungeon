extends TextureRect

@export var card_in_show:PackedScene

signal ok_button_pressed

# Called when the node enters the scene tree for the first time.
func _ready():
	# normal cards
	for ik in range(Global.MAXK):
		var node = card_in_show.instantiate()
		node.setup_k(ik)
		$ScrollContainer/HBoxContainer.add_child(node)
		
	# special cards
	for isp in range(Global.MAXSP):
		var node = card_in_show.instantiate()
		node.setup_sp(isp)
		$ScrollContainer/HBoxContainer.add_child(node)
		
	$CollectionRateLabel.text = "[center]" + str(Global.user.get_collection_rate()) + "%"

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_ok_button_pressed():
	ok_button_pressed.emit()
