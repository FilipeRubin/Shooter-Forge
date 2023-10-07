#include <GLFW/glfw3.h>
#include <string.h>
#include "Input/Keyboard.hpp"

using namespace Engine::Input;

static bool s_lastKeyState[GLFW_KEY_LAST];
static bool s_keyState[GLFW_KEY_LAST];

void Keyboard::Init()
{
	memset(s_keyState, false, sizeof(bool) * GLFW_KEY_LAST);
	memset(s_lastKeyState, false, sizeof(bool) * GLFW_KEY_LAST);
}

void Keyboard::Process()
{
	memcpy(s_lastKeyState, s_keyState, sizeof(bool) * GLFW_KEY_LAST);
}

void Keyboard::UpdateKeyState(int key, bool pressed)
{
	s_keyState[key] = pressed;
}

bool Keyboard::Pressed(Key key)
{
	return s_keyState[(int)key];
}

bool Keyboard::JustPressed(Key key)
{
	return s_keyState[(int)key] == true and s_lastKeyState[(int)key] == false;
}

bool Keyboard::JustReleased(Key key)
{
	return s_keyState[(int)key] == false and s_lastKeyState[(int)key] == true;
}
