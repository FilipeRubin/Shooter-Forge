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

Vector3 Transform::GetForward() const
{
	const glm::mat4 inverted = TransformUtilities::GenWorldHierarchyMatrix(*this);
	//const glm::mat4 inverted = glm::inverse(TransformUtilities::GenWorldHierarchyMatrix(*this));
	const glm::vec3 forward = normalize(glm::vec3(inverted[2]));
	return -FROM_GLM_VEC3(forward);
}

Vector3 Transform::GetRight() const
{
	const glm::mat4 inverted = TransformUtilities::GenWorldHierarchyMatrix(*this);
	//const glm::mat4 inverted = glm::inverse(TransformUtilities::GenWorldHierarchyMatrix(*this));
	const glm::vec3 right = normalize(glm::vec3(inverted[0]));
	return FROM_GLM_VEC3(right);
}