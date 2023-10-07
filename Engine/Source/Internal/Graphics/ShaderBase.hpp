#pragma once
#include <glad/glad.h>

// class ShaderBase
//
// Purpose: Be a high-level base abstraction for OpenGL shaders, but not as high-level enough to be accessible from outside of the project.
// Note: Each derived should implement its own shader in the Load() method.

namespace Engine::Graphics
{
	class ShaderBase
	{
	public:
		ShaderBase();
		virtual ~ShaderBase();
		virtual void Load(const char* vertexShaderSource, const char* fragmentShaderSource) = 0;
		virtual void Use() = 0;
		// Deleted
		ShaderBase           (ShaderBase&& other) noexcept = delete;
		ShaderBase& operator=(ShaderBase&& other) noexcept = delete;
		ShaderBase           (const ShaderBase& other) = delete;
		ShaderBase& operator=(const ShaderBase& other) = delete;
	protected:
		GLuint m_program;
		void Unload();
	};
}