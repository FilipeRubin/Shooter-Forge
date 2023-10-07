#include "Gameplay/Player.hpp"
#include "Graphics/Camera.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Utilities/Math.hpp"
#include "Utilities/Time.hpp"
#include "Utilities/Vector2.hpp"
#include "Utilities/Vector3.hpp"
#include <corecrt_math.h>
#include <iostream>

#define CLAMP(value, min, max) (value < min ? min : value > max ? max : value)

using namespace Engine::Gameplay;
using namespace Engine::Graphics;
using namespace Engine::Utilities;
using namespace Engine::Input;

void Player::Init()
{
	camera.transform.pParent = &transform;
	camera.transform.position = Vector3(0.0f, 1.0f, 0.0f);
}

void Player::Process()
{
	bool lockMouse = Mouse::GetLockMouse();

	if (Keyboard::JustPressed(Key::ESCAPE))
		Mouse::SetLockMouse(!lockMouse);
	ProcessMovement();

	if (lockMouse)
		ProcessMouseLook();
}

inline void Player::ProcessMovement()
{
	Vector3 direction = Vector3();
	if (Keyboard::Pressed(Key::W))
	{
		direction.z -= cosf(transform.rotation.y);
		direction.x += sinf(transform.rotation.y);
	}
	if (Keyboard::Pressed(Key::S))
	{
		direction.z += cosf(transform.rotation.y);
		direction.x -= sinf(transform.rotation.y);
	}
	if (Keyboard::Pressed(Key::A))
	{
		direction.z -= sinf(transform.rotation.y);
		direction.x -= cosf(transform.rotation.y);
	}
	if (Keyboard::Pressed(Key::D))
	{
		direction.z += sinf(transform.rotation.y);
		direction.x += cosf(transform.rotation.y);
	}
	if (Keyboard::Pressed(Key::SPACE))
	{
		direction.y += 1.0f;
	}
	if (Keyboard::Pressed(Key::LEFT_CONTROL))
	{
		direction.y -= 1.0f;
	}

	direction.Normalize();

	float speed = Keyboard::Pressed(Key::LEFT_SHIFT) ? 25.0f : 12.0f;

	m_velocity = m_velocity.Lerp(direction * speed, Time::GetDeltaTime() * 10.0f);

	transform.position += m_velocity * Time::GetDeltaTime();
}

inline void Player::ProcessMouseLook()
{
	Vector2 mouseDir = Input::Mouse::GetMouseMovement();
	transform.rotation.y -= mouseDir.x * 0.01f;
	camera.transform.rotation.x -= mouseDir.y * 0.01f;
	camera.transform.rotation.x = CLAMP(camera.transform.rotation.x, -Math::HALF_PI, Math::HALF_PI);
}
