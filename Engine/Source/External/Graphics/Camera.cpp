#include "Camera.hpp"
#include "Graphics/Renderer.hpp"

using namespace Engine::Graphics;

Camera Camera::defaultCamera = Camera();
Camera* Camera::pCurrentCamera = &defaultCamera;

Camera::Camera() :
	aspect(1.0f),
	near(0.1f),
	far(100.0f),
	fov(65.0f)
{
	aspect = Renderer::windowSize.x / Renderer::windowSize.y;
	if (pCurrentCamera == &defaultCamera)
	{
		pCurrentCamera = this;
	}
}

Camera::Camera(float _aspect, float _near, float _far, float _fov) :
	aspect(_aspect),
	near(_near),
	far(_far),
	fov(_fov)
{
	if (pCurrentCamera == &defaultCamera)
	{
		pCurrentCamera = this;
	}
}

Camera::~Camera()
{
	if (pCurrentCamera == this)
	{
		pCurrentCamera = &defaultCamera;
	}
}
