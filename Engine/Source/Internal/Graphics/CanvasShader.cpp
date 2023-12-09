#include "CanvasShader.hpp"
#include "ShaderLoader.hpp"
#include "Renderer.hpp"
#include "Graphics/Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

CanvasShader::CanvasShader() :
	ShaderBase(),
	m_uScreenResolution(0),
	m_uScreenAnchor(0),
	m_uSize(0),
	m_uPosition(0),
	m_uRotation(0)
{
}

void CanvasShader::Load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	Unload();
	m_program = ShaderLoader::Load(vertexShaderSource, fragmentShaderSource);
	Use();

	m_uScreenResolution = glGetUniformLocation(m_program, "u_screenResolution");
	m_uScreenAnchor     = glGetUniformLocation(m_program, "u_screenAnchor");
	m_uSize             = glGetUniformLocation(m_program, "u_size");
	m_uPosition         = glGetUniformLocation(m_program, "u_position");
	m_uRotation         = glGetUniformLocation(m_program, "u_rotation");
}

void CanvasShader::Use()
{
	Vector2 screenSize = Renderer::windowSize;
	glUseProgram(m_program);
	glUniform2f(m_uScreenResolution, screenSize.x, screenSize.y);

}

void CanvasShader::SetTexture(const Texture& texture) const
{
	glActiveTexture(GL_TEXTURE0);
	texture.Use();
}

void CanvasShader::SetScreenAnchor(const Vector2& screenAnchor) const
{
	glUniform2f(m_uScreenAnchor, screenAnchor.x, screenAnchor.y);
}

void CanvasShader::SetSize(const Vector2& size) const
{
	glUniform2f(m_uSize, size.x, size.y);
}

void CanvasShader::SetPosition(const Vector2& position) const
{
	glUniform2f(m_uPosition, position.x, position.y);
}

void CanvasShader::SetRotation(const float& rotation) const
{
	glm::mat3 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix3fv(m_uRotation, 1, GL_FALSE, &rotationMatrix[0][0]);
}
