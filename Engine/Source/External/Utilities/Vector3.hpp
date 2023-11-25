#pragma once

namespace Engine::Utilities
{
	struct Vector3
	{
		float x, y, z;

		Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
		Vector3 Cross(const Vector3& other) const;
		float DistanceTo(const Vector3& other) const;
		float Dot(const Vector3& other) const;
		float Magnitude() const;
		Vector3 Lerp(Vector3 to, float weight) const;
		void Normalize();
		Vector3 Normalized() const;

		// Operators
		bool operator==(const Vector3& other);
		void operator+=(const Vector3& other);
		void operator*=(const float& value);
	};
	Vector3 operator-(const Vector3& value);
	Vector3 operator+(const Vector3& v1, const Vector3& v2);
	Vector3 operator-(const Vector3& v1, const Vector3& v2);
	Vector3 operator*(const Vector3& v1, const Vector3& v2);
	Vector3 operator*(const Vector3& vector, const float& value);
}