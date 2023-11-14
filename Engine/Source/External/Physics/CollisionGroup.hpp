#pragma once
#include <string>

namespace Engine::Physics
{
	class Collider;
	class CollisionGroup
	{
	public:
		CollisionGroup();
		~CollisionGroup();
		void AddCollider(Collider* pCollider);
		void RemoveCollider(Collider* pCollider);
		bool IsIntersecting(const Collider& collider) const;
	private:
		Collider** m_colliderArray;
		size_t m_colliderArraySize;
		void ExpandArray();
	};
}