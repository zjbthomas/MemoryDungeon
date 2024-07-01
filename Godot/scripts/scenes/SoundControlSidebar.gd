extends HBoxContainer

@onready var bgm_staus_label = $SoundControlPanel/MarginContainer/VBoxContainer/BGMPanel/VBoxContainer/BGMStatusLabel
@onready var fx_staus_label = $SoundControlPanel/MarginContainer/VBoxContainer/FXPanel/VBoxContainer/FXStatusLabel

# Called when the node enters the scene tree for the first time.
func _ready():
	$SoundControlPanel/MarginContainer.visible = false
	$SoundControlPanel.custom_minimum_size.x = 0
	
	# update labels as is_muted may change in different scenes
	_update_bgm_staus_label()
	_update_fx_staus_label()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_mouse_entered():
	var tween = get_tree().create_tween()
	tween.tween_property($SoundControlPanel, "custom_minimum_size:x", 60, 0.1) # TODO: magic number: 60
	
	tween.tween_callback(func(): $SoundControlPanel/MarginContainer.visible = true)

func _on_mouse_exited():
	$SoundControlPanel/MarginContainer.visible = false
	
	var tween = get_tree().create_tween()
	tween.tween_property($SoundControlPanel, "custom_minimum_size:x", 0, 0.05)

func _on_bgm_button_pressed():
	BGM.switch()
	
	_update_bgm_staus_label()

func _on_fx_button_pressed():
	SoundEffect.switch()
	
	_update_fx_staus_label()
		
func _update_bgm_staus_label():
	if (!BGM.is_muted):
		bgm_staus_label.text = "[center]ON"
	else:
		bgm_staus_label.text = "[center]OFF"
		
func _update_fx_staus_label():
	if (!SoundEffect.is_muted):
		fx_staus_label.text = "[center]ON"
	else:
		fx_staus_label.text = "[center]OFF"
