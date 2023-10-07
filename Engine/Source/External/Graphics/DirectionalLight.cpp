#include "Graphics/DirectionalLight.hpp"

using namespace Engine::Graphics;
using namespace Engine::Utilities;

DirectionalLight DirectionalLight::defaultDirectionalLight = DirectionalLight(
	Vector3(0.5f, 0.5f, 0.5f), // Ambient
	Vector3(0.5f, 0.5f, 0.5f), // Color
	Vector3(0.0f, 1.0f, 0.0f) // Direction
);
DirectionalLight* DirectionalLight::pCurrentDirectionalLight = &defaultDirectionalLight;

DirectionalLight::DirectionalLight(Vector3 _ambient, Vector3 _color, Vector3 _direction):
	ambient(_ambient),
	color(_color),
	direction(_direction)
{
}

bool DirectionalLight::operator==(const DirectionalLight& other)
{
	return
		other.ambient == ambient and
		other.color == color and
		other.direction == direction;
}

bool DirectionalLight::operator!=(const DirectionalLight& other)
{
	return
		other.ambient != ambient or
		other.color != color or
		other.direction != direction;
}
