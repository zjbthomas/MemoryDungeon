extends TextureRect

signal ok_button_pressed(n_erase, n_level_k, n_rows, n_pop)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_ok_button_pressed():
	ok_button_pressed.emit($ATKSpinBox.value, $KSpinBox.value, $RowSpinBox.value, $RSpinBox.value)
