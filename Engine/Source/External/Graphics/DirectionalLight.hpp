#pragma once
#include "Utilities/Vector3.hpp"

// class DirectionalLight
//
// Purpose: Serve as a data container for information about a Directional Light to be used to lit a scene.
// Note: Only one DirectionalLight can be used at the same time (WorldShader dictates this rule).

namespace Engine::Graphics
{
	class DirectionalLight
	{
	public:
		static DirectionalLight defaultDirectionalLight;
		static DirectionalLight* pCurrentDirectionalLight;
		Utilities::Vector3 ambient;
		Utilities::Vector3 color;
		Utilities::Vector3 direction;
		DirectionalLight(Utilities::Vector3 _ambient = Utilities::Vector3(), Utilities::Vector3 _color = Utilities::Vector3(), Utilities::Vector3 _direction = Utilities::Vector3());
		bool operator==(const DirectionalLight& other);
		bool operator!=(const DirectionalLight& other);
	};
}