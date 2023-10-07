#include <GLFW/glfw3.h>
#include "Input/Mouse.hpp"
#include <vcruntime_string.h>

using namespace Engine::Input;
using namespace Engine::Utilities;

// Cursor position related
static bool s_lockMouse = false;
static Vector2 s_lastPos = Vector2();
static Vector2 s_currPos = Vector2();

// Button related
static bool s_lastButtonState[GLFW_MOUSE_BUTTON_LAST];
static bool s_buttonState[GLFW_MOUSE_BUTTON_LAST];

void Mouse::Init(Vector2 initPos)
{
	s_lastPos = initPos;
	s_currPos = initPos;
	memset(s_lastButtonState, false, sizeof(bool) * GLFW_MOUSE_BUTTON_LAST);
	memset(s_buttonState, false, sizeof(bool) * GLFW_MOUSE_BUTTON_LAST);
}

void Mouse::Process()
{
	memcpy(s_lastButtonState, s_buttonState, sizeof(bool) * GLFW_MOUSE_BUTTON_LAST);
}

void Mouse::SetPos(Utilities::Vector2 pos)
{
	s_lastPos = s_currPos;
	s_currPos = pos;
}

void Mouse::UpdateButtonState(int button, bool pressed)
{
	s_buttonState[button] = pressed;
}

void Mouse::SetLockMouse(bool value)
{
	s_lockMouse = value;
}

bool Mouse::GetLockMouse()
{
	return s_lockMouse;
}

Vector2 Mouse::GetMouseMovement()
{
	return s_lastPos - s_currPos;
}

bool Mouse::Pressed(MouseButton button)
{
	return s_buttonState[(int)button];
}

bool Mouse::JustPressed(int button)
{
	return s_buttonState[button] == true and s_lastButtonState[button] == false;
}

bool Mouse::JustReleased(int button)
{
	return s_buttonState[button] == false and s_lastButtonState[button] == true;
}
