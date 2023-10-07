#include "Utilities/Vector2.hpp"
#include <corecrt_math.h>

using namespace Engine::Utilities;

Vector2::Vector2(float _x, float _y)
	:x(_x), y(_y)
{
}

void Vector2::Normalize()
{
	if (x == 0.0f and y == 0.0f)
		return;

	float magnitude = sqrtf(x * x + y * y);

	x /= magnitude;
	y /= magnitude;
}

void Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator*=(const float& value)
{
	x *= value;
	y *= value;
}

Vector2 Engine::Utilities::operator+(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 Engine::Utilities::operator-(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}
