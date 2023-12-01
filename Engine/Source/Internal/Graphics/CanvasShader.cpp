#include "CanvasShader.hpp"
#include "ShaderLoader.hpp"
#include "Renderer.hpp"

using namespace Engine::Graphics;
using namespace Engine::Utilities;

CanvasShader::CanvasShader() :
	ShaderBase(),
	m_lastScreenSize(Vector2()),
	m_uPosition(Vector2()),
	m_uRotation(0.0f)
{
}

void CanvasShader::Load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	Unload();
	m_program = ShaderLoader::Load(vertexShaderSource, fragmentShaderSource);
	m_lastScreenSize = Renderer::windowSize;
}

void CanvasShader::Use()
{
	m_lastScreenSize = Renderer::windowSize;
	glUseProgram(m_program);
}
