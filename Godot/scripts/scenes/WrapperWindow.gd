extends Window

var _loaded_gui

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func load_window(name):
	# reset the size
	size = Vector2(0, 0)
	
	_loaded_gui = load(Global.WINDOW_TYPE.get(name)).instantiate()
	add_child(_loaded_gui)

func get_loaded_window():
	return _loaded_gui
