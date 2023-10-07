#pragma once

namespace Engine::Utilities
{
	struct Vector2
	{
		float x, y;

		Vector2(float _x = 0.0f, float _y = 0.0f);
		void Normalize();

		// Operators
		void operator+=(const Vector2& other);
		void operator*=(const float& value);
	};

	Vector2 operator+(const Vector2& v1, const Vector2& v2);
	Vector2 operator-(const Vector2& v1, const Vector2& v2);
}