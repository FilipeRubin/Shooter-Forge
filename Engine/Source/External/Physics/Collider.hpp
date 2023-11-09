#pragma once
#include <vector>
#include "Utilities/Vector3.hpp"
#include "Utilities/Transform.hpp"

namespace Engine::Physics
{
	class Simplex;
	class CollisionPoints;
	class Collider
	{
	public:
		Utilities::Transform transform;
		Collider();
		~Collider();
		bool IsIntersecting(const Collider& other) const;
		void Load(const char* filePath);
	private:
		const Utilities::Vector3* m_pointsArray;
		size_t m_pointsArraySize;
		Utilities::Vector3 FarthestPointInDirection(const Utilities::Vector3& direction) const;
		Utilities::Vector3 Support(const Collider& other, const Utilities::Vector3& direction) const;
		bool NextSimplex(Simplex& simplex, Utilities::Vector3& direction) const;
		bool SameDirection(const Utilities::Vector3& a, const Utilities::Vector3& b) const;
		bool LineCase(Simplex& simplex, Utilities::Vector3& direction) const;
		bool TriangleCase(Simplex& simplex, Utilities::Vector3& direction) const;
		bool TetrahedronCase(Simplex& simplex, Utilities::Vector3& direction) const;
		//CollisionPoints EPA(const Simplex& simplex, const Collider& other);
	};
}