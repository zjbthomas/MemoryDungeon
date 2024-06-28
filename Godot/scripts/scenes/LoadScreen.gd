extends ColorRect

@export var login_scene: PackedScene

# Called when the node enters the scene tree for the first time.
func _ready():
	_load_game_resources()
	
	get_tree().change_scene_to_packed(login_scene)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _load_game_resources():
	$VBoxContainer/ProgressBar.value = 0

	# load streams
	SoundEffect.load_streams()
	
	# finish loading
	$VBoxContainer/ProgressBar.value = 100
