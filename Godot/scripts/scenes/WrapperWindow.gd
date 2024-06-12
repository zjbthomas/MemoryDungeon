extends Window

@export var gui:Dictionary

var _loaded_gui

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func load_window(name):
	_loaded_gui = gui.get(name).instantiate()
	add_child(_loaded_gui)

func get_loaded_window():
	return _loaded_gui

func completed():
	hide()
	_loaded_gui.queue_free()
