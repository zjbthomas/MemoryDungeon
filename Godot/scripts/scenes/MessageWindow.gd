extends Window

signal ok_button_clicked

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func setup_ui(title, message, is_image_clickable):
	$MessageWindowGUI/Background/TitleLabel.text = "[center][b]" + title
	$MessageWindowGUI/Background/MessageLabel.text = "[b]" + message
	# TODO: is_image_clickable

func _on_message_window_gui_ok_button_clicked():
	ok_button_clicked.emit()
	queue_free()
