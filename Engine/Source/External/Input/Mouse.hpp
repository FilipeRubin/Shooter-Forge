#pragma once
#include "Utilities/Vector2.hpp"

namespace Engine::Input
{
	enum class MouseButton
	{
		MOUSE_BUTTON_LEFT = 0,
		MOUSE_BUTTON_RIGHT = 1,
		MOUSE_BUTTON_MIDDLE = 2,
		MOUSE_BUTTON_4 = 3,
		MOUSE_BUTTON_5 = 4,
		MOUSE_BUTTON_6 = 5,
		MOUSE_BUTTON_7 = 6,
		MOUSE_BUTTON_8 = 7
	};

	class Mouse
	{
	private:
		friend class Core;
		static void Init(Utilities::Vector2 initPos);
		static void Process();
		static void SetPos(Utilities::Vector2 pos);
		static void UpdateButtonState(int button, bool pressed);
	public:
		// If true, locks the mouse in the center of the screen and makes it invisible
		static void SetLockMouse(bool value);
		static bool GetLockMouse();
		static Utilities::Vector2 GetMouseMovement();
		static bool Pressed(MouseButton button);
		static bool JustPressed(MouseButton button);
		static bool JustReleased(MouseButton button);
	};
}