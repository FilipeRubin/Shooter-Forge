#pragma once
#include <glm/gtc/matrix_transform.hpp>

// static class TransformHierarchy
//
// Purpose: Provide common operations involving Transform

namespace Engine::Utilities
{
	class Transform;
	class TransformUtilities
	{
	public:
		static glm::mat4 GenWorldMatrix(const Transform& transform);
		static glm::mat4 GenViewMatrix(const Transform& transform);
		static glm::mat4 GenWorldHierarchyMatrix(const Transform& transform);
		static glm::mat4 GenViewHierarchyMatrix(const Transform& transform);
	};
}