#include "Simplex.hpp"
#include <vcruntime_string.h>

using namespace Engine::Physics;
using namespace Engine::Utilities;

Simplex::Simplex()
	:m_points(), m_size(0U)
{}

void Simplex::Clear()
{
	m_size = 0U;
}

void Simplex::PushFront(const Vector3& point)
{
	memmove(&(m_points[1]), m_points, sizeof(m_points[0]) * 3);

	m_points[0] = point;

	if (m_size < 4)
		m_size++;
}

size_t Simplex::GetSize() const
{
	return m_size;
}

void Simplex::ToVector3Array(Vector3(&result)[4]) const
{
	memcpy(result, m_points, sizeof(Vector3) * 4);
}

Vector3& Simplex::operator[](size_t index)
{
	return m_points[index];
}
