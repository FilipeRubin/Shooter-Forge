#include "TransformUtilities.hpp"
#include "Utilities/Transform.hpp"

using namespace Engine::Utilities;

glm::mat4 TransformUtilities::GenWorldMatrix(const Transform& transform)
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, transform.position.z));
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), transform.rotation.x, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), transform.rotation.y, glm::vec3(0.0f, -1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), transform.rotation.z, glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
	return translation * rotationZ * rotationY * rotationX * scale;
}

glm::mat4 TransformUtilities::GenViewMatrix(const Transform& transform)
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-transform.position.x, -transform.position.y, -transform.position.z));
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	return rotationZ * rotationY * rotationX * translation;
}

glm::mat4 TransformUtilities::GenWorldHierarchyMatrix(const Transform& transform)
{
	const Transform* pChild = &transform;
	const Transform* pParent = transform.pParent;

	glm::mat4 world = GenWorldMatrix(transform);

	while (pParent != nullptr)
	{
		world = GenWorldMatrix(*pParent) * world;
		pChild = pParent;
		pParent = pParent->pParent;
	}

	return world;
}

glm::mat4 TransformUtilities::GenViewHierarchyMatrix(const Transform& transform)
{
	const Transform* pChild = &transform;
	const Transform* pParent = transform.pParent;

	glm::mat4 view = GenViewMatrix(transform);

	while (pParent != nullptr)
	{
		view = view * GenViewMatrix(*pParent);
		pChild = pParent;
		pParent = pParent->pParent;
	}

	return view;
}
