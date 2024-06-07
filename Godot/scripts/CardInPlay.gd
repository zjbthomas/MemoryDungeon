extends Node


# Called when the node enters the scene tree for the first time.
func _ready():
	$CardFlip.play("card_flip")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_card_flip_animation_finished(anim_name):
	$CardBack/Cards.play("1")
