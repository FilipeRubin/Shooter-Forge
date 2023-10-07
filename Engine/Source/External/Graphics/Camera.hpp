#pragma once
#include "Utilities/Transform.hpp"

// class Camera
//  
// Purpose: Container for camera values. Literally just a container and a static member pointing to a "current" one.

namespace Engine::Graphics
{
	class Camera
	{
	public:
		static Camera defaultCamera;
		static Camera* pCurrentCamera;
	public:
		float aspect;
		float near;
		float far;
		float fov;
		Utilities::Transform transform;
		Camera();
		Camera(float _aspect, float _near, float _far, float _fov);
		~Camera();
	};
}