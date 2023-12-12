#include "Collider.hpp"
#include "Physics/Simplex.hpp"
#include "Physics/ColliderLoader.hpp"
#include "Utilities/TransformUtilities.hpp"
#include "Input/Keyboard.hpp"
#include <iostream>

#define TO_GLM_VEC3(x) (*((glm::vec3*)&x))
#define FROM_GLM_VEC3(x) (*((Utilities::Vector3*)&x))

using namespace Engine::Physics;
using namespace Engine::Utilities;
using namespace std;

extern bool g_usingSphericalDetection;

Collider::Collider() :
	pMesh(nullptr),
	enabled(true),
	m_pointsArray(nullptr),
	m_pointsArraySize(0U),
	m_minBoundingBox(Vector3(FLT_MAX, FLT_MAX, FLT_MAX)),
	m_maxBoundingBox(Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX)),
	m_radius(0.0f),
	m_lastDirection(Vector3(0.0f, 1.0f, 0.0f))
{
}

Collider::~Collider()
{
	delete[] m_pointsArray;
}

bool Collider::IsIntersecting(const Collider& other) const
{
	if (!enabled)
		return false;
	if (g_usingSphericalDetection)
	{
		if (!HasSphericalIntersection(other))
			return false;
	}
	else
	{
		if (!HasAABBIntersection(other))
			return false;
	}

	Simplex simplex;
	Vector3 direction = m_lastDirection;
	Vector3 supportPoint = Support(other, direction);
	simplex.PushFront(supportPoint);
	direction = -supportPoint;

	while (true)
	{
		supportPoint = Support(other, direction);
		if (supportPoint.Dot(direction) <= 0.0f)
		{
			m_lastDirection = direction;
			return false;
		}
		simplex.PushFront(supportPoint);

		if (NextSimplex(simplex, direction))
		{
			m_lastDirection = direction;
			return true;
		}
	}

	m_lastDirection = direction;
	return false;
}

void Collider::Load(const char* filePath)
{
	delete[] m_pointsArray;

	ColliderLoader::LoadFromFile(filePath, m_pointsArray, m_pointsArraySize);

	for (size_t i = 0; i < m_pointsArraySize; i++)
	{
		if (m_pointsArray[i].x < m_minBoundingBox.x) m_minBoundingBox.x = m_pointsArray[i].x;
		if (m_pointsArray[i].y < m_minBoundingBox.y) m_minBoundingBox.y = m_pointsArray[i].y;
		if (m_pointsArray[i].z < m_minBoundingBox.z) m_minBoundingBox.z = m_pointsArray[i].z;

		if (m_pointsArray[i].x > m_maxBoundingBox.x) m_maxBoundingBox.x = m_pointsArray[i].x;
		if (m_pointsArray[i].y > m_maxBoundingBox.y) m_maxBoundingBox.y = m_pointsArray[i].y;
		if (m_pointsArray[i].z > m_maxBoundingBox.z) m_maxBoundingBox.z = m_pointsArray[i].z;
		
		float pointRadius = m_pointsArray[i].Magnitude();
		if (pointRadius > m_radius)
			m_radius = pointRadius;
	}
}

bool Collider::HasAABBIntersection(const Collider& other) const
{
	const Vector3& thisMin = transform.GetWorldPosition() + m_minBoundingBox;
	const Vector3& thisMax = transform.GetWorldPosition() + m_maxBoundingBox;
	const Vector3& otherMin = other.transform.GetWorldPosition() + other.m_minBoundingBox;
	const Vector3& otherMax = other.transform.GetWorldPosition() + other.m_maxBoundingBox;
	
	return
		(thisMin.x < otherMax.x and thisMax.x > otherMin.x) and
		(thisMin.y < otherMax.y and thisMax.y > otherMin.y) and
		(thisMin.z < otherMax.z and thisMax.z > otherMin.z);
}

bool Collider::HasSphericalIntersection(const Collider& other) const
{
	return transform.GetWorldPosition().DistanceTo(other.transform.GetWorldPosition()) < (m_radius + other.m_radius);
}

Vector3 Collider::FarthestPointInDirection(const Utilities::Vector3& direction) const
{
	Vector3 farthestPoint;
	float farthestDirection = -FLT_MAX;
	for (size_t i = 0; i < m_pointsArraySize; i++)
	{
		glm::mat4 transformationMatrix = TransformUtilities::GenWorldHierarchyMatrix(transform);
		glm::vec3 transformedVertex = glm::vec3(transformationMatrix * glm::vec4(TO_GLM_VEC3(m_pointsArray[i]), 1.0f));
		const Vector3& transformedConvertedVertex = FROM_GLM_VEC3(transformedVertex);

		float pointDot = transformedConvertedVertex.Dot(direction);
		if (pointDot > farthestDirection)
		{
			farthestPoint = transformedConvertedVertex;
			farthestDirection = pointDot;
		}
	}
	return farthestPoint;
}

Vector3 Collider::Support(const Collider& other, const Vector3& direction) const
{
	return FarthestPointInDirection(direction) - other.FarthestPointInDirection(-direction);
}

bool Collider::NextSimplex(Simplex& simplex, Vector3& direction) const
{
	switch (simplex.GetSize())
	{
	case 2:
		return LineCase(simplex, direction);
	case 3:
		return TriangleCase(simplex, direction);
	case 4:
		return TetrahedronCase(simplex, direction);
	}

	// Never should be here
	return false;
}

bool Collider::SameDirection(const Vector3& a, const Vector3& b) const
{
	return a.Dot(b) > 0.0f;
}

bool Collider::LineCase(Simplex& simplex, Vector3& direction) const
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];

	Vector3 ab = b - a;
	Vector3 ao =   - a;

	if (SameDirection(ab, ao))
	{
		direction = ab.Cross(ao).Cross(ab);
	}
	else
	{
		simplex.Clear();
		simplex.PushFront(a);
		direction = ao;
	}

	return false;
}

bool Collider::TriangleCase(Simplex& simplex, Vector3& direction) const
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ao =   - a;

	Vector3 abc = ab.Cross(ac);

	if (SameDirection(abc.Cross(ac), ao))
	{
		if (SameDirection(ac, ao))
		{
			simplex.Clear();
			simplex.PushFront(c);
			simplex.PushFront(a);
			direction = ac.Cross(ao).Cross(ac);
		}
		else
		{
			simplex.Clear();
			simplex.PushFront(b);
			simplex.PushFront(a);
			return LineCase(simplex, direction);
		}
	}
	else
	{
		if (SameDirection(ab.Cross(abc), ao))
		{
			simplex.Clear();
			simplex.PushFront(b);
			simplex.PushFront(a);
			return LineCase(simplex, direction);
		}
		else
		{
			if (SameDirection(abc, ao))
			{
				direction = abc;
			}
			else
			{
				simplex.Clear();
				simplex.PushFront(b);
				simplex.PushFront(c);
				simplex.PushFront(a);
				direction = -abc;
			}
		}
	}

	return false;
}

bool Collider::TetrahedronCase(Simplex& simplex, Vector3& direction) const
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];
	Vector3 d = simplex[3];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ad = d - a;
	Vector3 ao =   - a;

	Vector3 abc = ab.Cross(ac);
	Vector3 acd = ac.Cross(ad);
	Vector3 adb = ad.Cross(ab);

	if (SameDirection(abc, ao))
	{
		simplex.Clear();
		simplex.PushFront(c);
		simplex.PushFront(b);
		simplex.PushFront(a);
		return TriangleCase(simplex, direction);
	}
	if (SameDirection(acd, ao))
	{
		simplex.Clear();
		simplex.PushFront(d);
		simplex.PushFront(c);
		simplex.PushFront(a);
		return TriangleCase(simplex, direction);
	}
	if (SameDirection(adb, ao))
	{
		simplex.Clear();
		simplex.PushFront(a);
		simplex.PushFront(d);
		simplex.PushFront(b);
		return TriangleCase(simplex, direction);
	}

	return true;
}
