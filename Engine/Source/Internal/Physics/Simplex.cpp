#include "Simplex.hpp"
#include <vcruntime_string.h>

using namespace Engine::Physics;
using namespace Engine::Utilities;

Simplex::Simplex()
	:m_points(), m_size(0U)
{}

void Simplex::Clear()
{
	for (size_t i = 0; i < 4; i++)
		m_points[i] = Vector3(0.0f, 0.0f, 0.0f);

	m_size = 0U;
}

void Simplex::PushFront(const Vector3& point)
{
	m_points[3] = m_points[2];
	m_points[2] = m_points[1];
	m_points[1] = m_points[0];
	m_points[0] = point;

	if (m_size < 4)
		m_size++;
}

size_t Simplex::GetSize() const
{
	return m_size;
}

Vector3& Simplex::operator[](size_t index)
{
	return m_points[index];
}
