#pragma once

#include "glm\glm.hpp"

enum InputType
{
	InputType_Unknown,
	InputType_Keyboard,
	InputType_MouseButton,
	InputType_MouseMovement,
};
enum KeyState
{
	KeyState_Unknown,
	KeyState_Pressed,
	KeyState_Released,
};
enum Key
{
	Key_Unknown,
	Key_Space,
	Key_Apostrophe,
	Key_Comma,
	Key_Minus,
	Key_Period,
	Key_Slash,
	Key_0,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	Key_Semicolon,
	Key_Equal,
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_LeftBracket,
	Key_Backslash,
	Key_RightBracket,
	Key_GraveAccent,
	Key_World1,
	Key_World2,
	Key_Escape,
	Key_Enter,
	Key_Tab,
	Key_Backspace,
	Key_Insert,
	Key_Delete,
	Key_Right,
	Key_Left,
	Key_Down,
	Key_Up,
	Key_PageUp,
	Key_PageDown,
	Key_Home,
	Key_End,
	Key_CapsLock,
	Key_ScrollLock,
	Key_NumLock,
	Key_PrintScreen,
	Key_Pause,
	Key_F1,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,
	Key_F13,
	Key_F14,
	Key_F15,
	Key_F16,
	Key_F17,
	Key_F18,
	Key_F19,
	Key_F20,
	Key_F21,
	Key_F22,
	Key_F23,
	Key_F24,
	Key_F25,
	Key_Pad0,
	Key_Pad1,
	Key_Pad2,
	Key_Pad3,
	Key_Pad4,
	Key_Pad5,
	Key_Pad6,
	Key_Pad7,
	Key_Pad8,
	Key_Pad9,
	Key_PadDecimal,
	Key_PadDivide,
	Key_PadMultiply,
	Key_PadSubtract,
	Key_PadAdd,
	Key_PadEnter,
	Key_PadEqual,
	Key_LeftShift,
	Key_LeftControl,
	Key_LeftAlt,
	Key_LeftSuper,
	Key_RightShift,
	Key_RightControl,
	Key_RightAlt,
	Key_RightSuper,
	Key_Menu,
};
enum MouseButton
{
	MouseButton_Unknown,
	MouseButton_Left,
	MouseButton_Middle,
	MouseButton_Right,
};
enum MouseButtonState
{
	MouseButtonState_Unknown,
	MouseButtonState_Down,
	MouseButtonState_Up,
};

struct KeyboardInput
{
	Key key;
	KeyState keyState;

	KeyboardInput(Key, KeyState);
};
struct MouseButtonInput
{
	MouseButton button;
	MouseButtonState state;
	glm::ivec2 position;

	MouseButtonInput(MouseButton, MouseButtonState, glm::ivec2 position);
};
struct MouseMovementInput
{
	glm::ivec2 movement;
	glm::ivec2 position;

	MouseMovementInput(glm::ivec2 movement, glm::ivec2 position);
};
struct Input
{
	InputType type;
	KeyboardInput keyboard;
	MouseButtonInput mouseButton;
	MouseMovementInput mouseMovement;

	Input(KeyboardInput);
	Input(MouseButtonInput);
	Input(MouseMovementInput);
};
