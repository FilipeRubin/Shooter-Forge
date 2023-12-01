#include "SpriteRenderer.hpp"
#include "Utilities/Vector2.hpp"
#include <glad/glad.h>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

unsigned int SpriteRenderer::s_vbo = 0U;
unsigned int SpriteRenderer::s_vao = 0U;

void SpriteRenderer::Init()
{
	Vector2 spriteVertices[]
	{
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f }
	};

	glGenBuffers(1, &s_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &s_vao);
	glBindVertexArray(s_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);
	glEnableVertexAttribArray(0U);

	const char* canvasVertexSource = R"(
)";

	const char* canvasFragmentSource = R"(
)";

	s_shader.Load(canvasVertexSource, canvasFragmentSource);
}

void SpriteRenderer::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void SpriteRenderer::Cleanup()
{
	glDeleteBuffers(1, &s_vbo);
	glDeleteVertexArrays(1, &s_vao);
}
