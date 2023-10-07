#pragma once
#include "Vector3.hpp"

namespace Engine::Utilities
{
	class Transform
	{
	public:
		Vector3 position;   // Local position, relative to its parent (if present).
		Vector3 rotation;   // Local rotation in Euler angles, relative to its parent (if present).
		Vector3 scale;      // Local scale, relative to its parent (if present).
		Transform* pParent; // If not nullptr, this transform will be relative to a parent's transform.
	public:
		Transform();
	};
}