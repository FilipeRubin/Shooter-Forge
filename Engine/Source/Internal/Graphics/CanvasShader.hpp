#pragma once

#include "ShaderBase.hpp"
#include "Utilities/Vector2.hpp"
#include "Utilities/Vector3.hpp"

// class CanvasShader
//
// Purpose: Specific implementation of shaders that are responsible for rendering 2D elements like HUDs and menus.

namespace Engine::Graphics
{
	class Texture;
	class CanvasShader : public ShaderBase
	{
	public:
		CanvasShader();
		void Load(const char* vertexShaderSource, const char* fragmentShaderSource) override;
		void Use() override;
		void SetTexture(const Texture& texture) const;
		void SetScreenAnchor(const Utilities::Vector2& screenAnchor) const;
		void SetSize(const Utilities::Vector2& size) const;
		void SetPosition(const Utilities::Vector2& position) const;
		void SetRotation(const float& rotation) const;
	private:
		GLint m_uScreenResolution;
		GLint m_uScreenAnchor;
		GLint m_uSize;
		GLint m_uPosition;
		GLint m_uRotation;
	};
}