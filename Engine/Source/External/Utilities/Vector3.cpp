#include "Utilities/Vector3.hpp"
#include "Utilities/Math.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <corecrt_math.h>
#include <vcruntime_string.h>

using namespace Engine::Utilities;

Vector3::Vector3(float _x, float _y, float _z)
	:x(_x), y(_y), z(_z)
{
}

float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
	if (x == 0.0f and y == 0.0f and z == 0.0f)
		return;

	float magnitude = sqrtf(x * x + y * y + z * z);

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

Vector3 Vector3::Normalized()
{
	if (x == 0.0f and y == 0.0f and z == 0.0f)
		return Vector3();

	float magnitude = sqrtf(x * x + y * y + z * z);

	return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 Vector3::Lerp(Vector3 to, float weight) const
{
	Vector3 res = *this;

	res.x = Math::Lerp(res.x, to.x, weight);
	res.y = Math::Lerp(res.y, to.y, weight);
	res.z = Math::Lerp(res.z, to.z, weight);

	return res;
}

Vector3 Engine::Utilities::operator-(const Vector3& value)
{
	return Vector3(-value.x, -value.y, -value.z);
}

Vector3 Engine::Utilities::operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 Engine::Utilities::operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 Engine::Utilities::operator*(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 Engine::Utilities::operator*(const Vector3& vector, const float& value)
{
	return Vector3(vector.x * value, vector.y * value, vector.z * value);
}

bool Vector3::operator==(const Vector3& other)
{
	return
		other.x == x and
		other.y == y and
		other.z == z;
}

/*bool Vector3::operator!=(const Vector3& other)
{
	return
		other.x != x or
		other.y != y or
		other.z != z;
}*/

void Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator*=(const float& value)
{
	x *= value;
	y *= value;
	z *= value;
}
