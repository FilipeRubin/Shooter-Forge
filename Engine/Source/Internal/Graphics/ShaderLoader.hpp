#pragma once

// static class ShaderLoader
//
// Purpose: Load shaders and return its Id.

namespace Engine::Graphics
{
	class ShaderLoader
	{
	public:
		static unsigned int Load(const char* vertexShaderSource, const char* fragmentShaderSource);
	private:
		static bool Check(unsigned int shader, unsigned int type); // Returns true if shader was compiled successfully, prints an error message otherwise.
	};
}
