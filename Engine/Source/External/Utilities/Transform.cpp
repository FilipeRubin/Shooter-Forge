#include "Utilities/Transform.hpp"

using namespace Engine::Utilities;

Transform::Transform() :
	position(Vector3(0.0f, 0.0f, 0.0f)),
	rotation(Vector3(0.0f, 0.0f, 0.0f)),
	scale   (Vector3(1.0f, 1.0f, 1.0f)),
	pParent (nullptr)
{
}

