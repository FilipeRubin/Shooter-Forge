#pragma once
#include <vector>
#include "Utilities/Vector3.hpp"
#include "Utilities/Transform.hpp"

namespace Engine::Physics
{
	class Simplex;
	class Collider
	{
	public:
		Utilities::Transform transform;
		std::vector<Utilities::Vector3> points;
		bool IsIntersecting(const Collider& other) const;
	private:
		Utilities::Vector3 FarthestPointInDirection(const Utilities::Vector3& direction) const;
		bool NextSimplex(Simplex& simplex, Utilities::Vector3& direction) const;
		bool SameDirection(const Utilities::Vector3& a, const Utilities::Vector3& b) const;
		bool LineCase(Simplex& simplex, Utilities::Vector3& direction) const;
		bool TriangleCase(Simplex& simplex, Utilities::Vector3& direction) const;
		bool TetrahedronCase(Simplex& simplex, Utilities::Vector3& direction) const;
	};
}