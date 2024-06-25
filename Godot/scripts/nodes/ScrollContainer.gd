extends ScrollContainer
# The script adds the ability to kinetic scroll for ScrollContainer
# It is necessary to check the state of the scroll when working with internal controls

# The variable allows you to disable the kinetic scroll
@export var kineticScrollEnable = true
# The variable determines the direction of the scroll
@export_enum("Horizontal", "Vertical") var scrollDirection = "Horizontal"
# Variable specifies how long it will continue scrolling
@export var kineticScrollTime = 0.3
# The variable determines the kinetic scroll length
@export var kineticScrollBias = 0.5
# The variable determines which offset to consider as a swipe
@export var swipeTolerance = 50

@export var swipeSensitivity = 1.0

# The variable shows the state of the scroll. Used to organize the work of internal controls
var swiping = false

var _swipePoint = null


func _ready():
	set_process_input(kineticScrollEnable)

func _input(event):
	if (not(event is InputEventMouseButton)) and (not(event is InputEventMouseMotion)):
		return
	# Check that the cursor is over the scroll area
	if (!self.get_global_rect().has_point(event.position)):
		swiping = false
		_swipePoint = null
		return
	# By pressing set the necessary variables
	if (event is InputEventMouseButton) and (event.pressed == true): 
		swiping = true
		if ((event.button_index == MOUSE_BUTTON_LEFT) or (event.button_index == MOUSE_BUTTON_RIGHT)):
			_swipePoint = event.position
		if ((event.button_index == MOUSE_BUTTON_WHEEL_UP) or (event.button_index == MOUSE_BUTTON_WHEEL_DOWN)):
			_swipePoint = Vector2(self.get_h_scroll(), self.get_v_scroll())
	if (swiping) and (event is InputEventMouseButton) and (event.pressed == false):
		# Swipe off if the cursor position has not changed
		if ((_swipePoint - event.position).length() < swipeTolerance):
			swiping = false
			_swipePoint = null
			return
		# Create a tween responsible for kinetic scrolling
		var tween = get_tree().create_tween()
		if ((event.button_index == MOUSE_BUTTON_LEFT) or (event.button_index == MOUSE_BUTTON_RIGHT)):
			if (scrollDirection == "Horizontal"):
				tween.tween_method(self.set_h_scroll, self.get_h_scroll(), 
					self.get_h_scroll() - kineticScrollBias*(event.position.x - _swipePoint.x), kineticScrollTime).set_trans(Tween.TRANS_LINEAR)
			if (scrollDirection == "Vertical"):
				tween.tween_method(self.set_v_scroll, self.get_v_scroll(), 
					self.get_v_scroll() - kineticScrollBias*(event.position.y - _swipePoint.y), kineticScrollTime).set_trans(Tween.TRANS_LINEAR)
		if ((event.button_index == MOUSE_BUTTON_WHEEL_UP) or (event.button_index == MOUSE_BUTTON_WHEEL_DOWN)):
			if (scrollDirection == "Horizontal"):
				tween.tween_method(self.set_h_scroll, self.get_h_scroll(), 
					self.get_h_scroll() + kineticScrollBias*(self.get_h_scroll() - _swipePoint.x), kineticScrollTime).set_trans(Tween.TRANS_LINEAR)
			if (scrollDirection == "Vertical"):
				tween.tween_method(self.set_v_scroll, self.get_v_scroll(), 
					self.get_v_scroll() + kineticScrollBias*(self.get_v_scroll() - _swipePoint.y), kineticScrollTime).set_trans(Tween.TRANS_LINEAR)
		tween.tween_callback(func(): swiping = false).set_delay(kineticScrollTime)
		tween.tween_callback(tween.kill).set_delay(kineticScrollTime)
		#tween.start()
		_swipePoint = null
	# Scrolling while moving the cursor
	if (_swipePoint != null) and (event is InputEventMouseMotion):
		if (scrollDirection == "Horizontal"):
			self.set_h_scroll(self.get_h_scroll() - swipeSensitivity * (event.position.x - _swipePoint.x))
		if (scrollDirection == "Vertical"):
			self.set_v_scroll(self.get_v_scroll() - swipeSensitivity * ( event.position.y - _swipePoint.y))


# The function provides disable/enable kinetic scrolling at runtime
func setKineticScrollEnable(enable: bool):
	kineticScrollEnable = enable
	set_process_input(enable)
