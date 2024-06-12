extends TextureRect

signal hero_selected(ix)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_area_mouse_entered(ix):
	$AnimatedSprite2D.play(ix)

func _on_area_pressed(ix):
	hero_selected.emit(ix)
