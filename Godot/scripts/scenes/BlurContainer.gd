extends ColorRect


# Called when the node enters the scene tree for the first time.
func _ready():
	# always hide as default when loaded
	visible = false
	$WrapperWindow.hide()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func activate():
	visible = true
	$WrapperWindow.popup_centered()
	
func complete():
	visible = false
	$WrapperWindow.hide()
	$WrapperWindow.get_loaded_window().queue_free()
