#include "Utilities/Transform.hpp"
#include "Utilities/TransformUtilities.hpp"
#include <glm/gtx/matrix_decompose.hpp>

#define FROM_GLM_VEC3(x) (*((Utilities::Vector3*)&x))

using namespace Engine::Utilities;

Transform::Transform() :
	position(Vector3(0.0f, 0.0f, 0.0f)),
	rotation(Vector3(0.0f, 0.0f, 0.0f)),
	scale   (Vector3(1.0f, 1.0f, 1.0f)),
	pParent (nullptr)
{
}

Vector3 Transform::GetWorldPosition() const
{
	glm::mat4 world = TransformUtilities::GenWorldHierarchyMatrix(*this);

	glm::vec3 scale;
	glm::quat orientation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(world, scale, orientation, translation, skew, perspective);

	Vector3 result = FROM_GLM_VEC3(translation);

	return result;
}

