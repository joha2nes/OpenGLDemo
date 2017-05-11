#include "Input.hpp"

KeyboardInput::KeyboardInput(Key k, KeyState ks)
	: key(k)
	, keyState(ks)
{}

MouseButtonInput::MouseButtonInput(MouseButton b, MouseButtonState s, glm::ivec2 p)
	: position(p)
	, button(b)
	, state(s)
{}

MouseMovementInput::MouseMovementInput(glm::ivec2 m, glm::ivec2 p)
	: movement(m)
	, position(p)
{}

Input::Input(KeyboardInput k)
	: type(InputType_Keyboard)
	, keyboard(k)
	, mouseButton(MouseButton_Unknown, MouseButtonState_Unknown, glm::ivec2(0))
	, mouseMovement(glm::ivec2(0), glm::ivec2(0))
{}
Input::Input(MouseButtonInput mb)
	: type(InputType_MouseButton)
	, keyboard(Key_Unknown, KeyState_Unknown)
	, mouseButton(mb)
	, mouseMovement(glm::ivec2(0), glm::ivec2(0))
{}
Input::Input(MouseMovementInput mm)
	: type(InputType_MouseMovement)
	, keyboard(Key_Unknown, KeyState_Unknown)
	, mouseButton(MouseButton_Unknown, MouseButtonState_Unknown, glm::ivec2(0))
	, mouseMovement(mm)
{}