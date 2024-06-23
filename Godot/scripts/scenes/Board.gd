extends GridContainer

@export var card_scene:PackedScene

signal card_button_pressed(ir, ic)

# Called when the node enters the scene tree for the first time.
func _ready():
	# create containers (ColorRect)
	for ir in range(Global.MAXR - 1, -1, -1):
		for ic in range(Global.MAXC):
			# we need these containers as invisible card will not occupy spaces in grid
			var node_container = ColorRect.new()
			node_container.set_name(get_container_name(ir, ic))
			add_child(node_container)
			
			var node_card = card_scene.instantiate()
			node_card.visible = false
			node_card.card_button_pressed.connect(_on_card_button_pressed.bind(ir, ic))
			node_container.add_child(node_card)
		
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func get_container_name(ir, ic):
	return "Space" + str(ir) + str(ic)

func update_one_card(ir, ic, card):
	# TODO: can we avoid get_child(0), or check if there is only one child?
	get_node(get_container_name(ir, ic)).get_child(0).update(card)

func _on_card_button_pressed(ir, ic):
	card_button_pressed.emit(ir, ic)
	
