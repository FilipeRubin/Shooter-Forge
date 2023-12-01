#pragma once
#include "CanvasShader.hpp"

namespace Engine::Graphics
{
	class SpriteRenderer
	{
	public:
		static void Init();
		static void Render();
		static void Cleanup();
	private:
		static unsigned int s_vbo;
		static unsigned int s_vao;
		static CanvasShader s_shader;
	};
}