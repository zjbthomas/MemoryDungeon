extends Node

const _STREAM_TYPE = {
	"card_flip": "res://musics//card_flip.mp3",
	"card_remove": "res://musics//card_remove.mp3",
	"card_cover": "res://musics//card_cover.mp3",
	"break": "res://musics//break.mp3",
	"gain_gold": "res://musics//gain_gold.mp3",
	"chaos": "res://musics//chaos.mp3",
	"positive_sp_cards": "res://musics//positive_sp_cards.mp3",
	"notification_ok": "res://musics//notification_ok.mp3",
	"notification_error": "res://musics//notification_error.mp3",
	"win": "res://musics//win.mp3",
	"lose": "res://musics//lose.mp3",
	"card_draw": "res://musics//card_draw.mp3",
	"lucky_draw": "res://musics//lucky_draw.mp3",
	"unlucky_draw": "res://musics//unlucky_draw.mp3",
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
