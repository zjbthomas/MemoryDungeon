extends Node

const _STREAM_TYPE = {
	"card_flip": "res://musics//card_flip.mp3",
	"card_remove": "res://musics//card_remove.mp3",
	"card_cover": "res://musics//card_cover.mp3",
}

var _streams = {}
	
# Called when the node enters the scene tree for the first time.
func _ready():
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func load_streams():
	for key in _STREAM_TYPE:
		_streams[key] = load(_STREAM_TYPE[key])
	
func play(name):
	$SoundEffectPlayer.stream = _streams.get(name)
	$SoundEffectPlayer.play()
