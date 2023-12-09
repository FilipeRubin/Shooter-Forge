#include "Sprite.hpp"
#include "Graphics/Renderer.hpp"
#include <glad/glad.h>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

unsigned int Sprite::s_vbo = 0U;
unsigned int Sprite::s_vao = 0U;

Sprite::Sprite() :
	rotation(0.0f),
	m_index(0U)
{
	m_index = Renderer::AddSprite(this);
}

Sprite::~Sprite()
{
	Renderer::RemoveSprite(m_index);
}

void Sprite::Render() const
{
	glBindVertexArray(s_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Sprite::Init()
{
	Vector2 vertices[4]
	{
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f }
	};

	glGenBuffers(1, &s_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &s_vao);
	glBindVertexArray(s_vao);
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2U, (void*)0);
	glEnableVertexAttribArray(0U);
}

void Sprite::Cleanup()
{
	glDeleteBuffers(1, &s_vbo);
	glDeleteVertexArrays(1, &s_vao);
}
