#pragma once

#include "ShaderBase.hpp"
#include "Utilities/Vector2.hpp"

// class CanvasShader
//
// Purpose: Specific implementation of shaders that are responsible for rendering 2D elements like HUDs and menus.

namespace Engine::Graphics
{
	class CanvasShader : public ShaderBase
	{
	public:
		CanvasShader();
		void Load(const char* vertexShaderSource, const char* fragmentShaderSource) override;
		void Use() override;
	private:
		Utilities::Vector2 m_lastScreenSize;
	};
}