#include "CollisionGroup.hpp"
#include "Collider.hpp"

using namespace Engine::Physics;

CollisionGroup::CollisionGroup()
	:m_colliderArray(new Collider*[5]{nullptr}), m_colliderArraySize(5U)
{
}

CollisionGroup::~CollisionGroup()
{
	delete[] m_colliderArray;
}

void CollisionGroup::AddCollider(Collider* pCollider)
{
	bool foundSlot = false;

	for (size_t i = 0; i < m_colliderArraySize; i++)
	{
		if (m_colliderArray[i] == nullptr)
		{
			m_colliderArray[i] = pCollider;
			foundSlot = true;
			return;
		}
	}

	// If no free place was found
	if (!foundSlot)
	{
		int slotIndex = m_colliderArraySize;
		ExpandArray();
		m_colliderArray[slotIndex] = pCollider;
	}
}

void CollisionGroup::RemoveCollider(Collider* pCollider)
{
	for (size_t i = 0; i < m_colliderArraySize; i++)
	{
		if (m_colliderArray[i] == pCollider)
		{
			m_colliderArray = nullptr;
			return;
		}
	}
}

bool CollisionGroup::IsIntersecting(const Collider& collider) const
{
	for (size_t i = 0; i < m_colliderArraySize; i++)
	{
		if (m_colliderArray[i] != nullptr and m_colliderArray[i]->IsIntersecting(collider))
		{
			return true;
		}
	}

	return false;
}

void CollisionGroup::ExpandArray()
{
	Collider** newArray = new Collider*[m_colliderArraySize * 2];

	memcpy(newArray, m_colliderArray, sizeof(Collider*) * m_colliderArraySize);
	memset(newArray + m_colliderArraySize, NULL, sizeof(Collider*) * m_colliderArraySize);
	
	delete[] m_colliderArray;
	m_colliderArray = newArray;
	m_colliderArraySize *= 2;
}
