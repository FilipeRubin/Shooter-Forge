#include "MeshData.hpp"
#include "glad/glad.h"
#include "MeshLoader.hpp"

using namespace Engine::Graphics;

MeshData::MeshData()
	:m_vbo(0U), m_vao(0U), m_ebo(0U), m_indexCount(0U)
{
}

MeshData::MeshData(MeshData&& other) noexcept
	:m_vbo(other.m_vbo), m_vao(other.m_vao), m_ebo(other.m_ebo), m_indexCount(other.m_indexCount)
{
	other.m_vbo = 0U;
	other.m_vao = 0U;
	other.m_ebo = 0U;
	other.m_indexCount = 0U;
}

MeshData::~MeshData()
{
	Unload();
}

MeshData& MeshData::operator=(MeshData&& other) noexcept
{
	if (this != &other)
	{
		m_vbo = other.m_vbo;
		m_vao = other.m_vao;
		m_ebo = other.m_ebo;
		m_indexCount = other.m_indexCount;

		other.m_vbo = 0U;
		other.m_vao = 0U;
		other.m_ebo = 0U;
		other.m_indexCount = 0U;
	}
	return *this;
}

void MeshData::Load(const char* filePath)
{
	Unload();

	float*        vertexArray;
	size_t        vertexArraySize;
	unsigned int* indexArray;
	size_t        indexArraySize;
	MeshLoader::LoadFromFile(filePath, vertexArray, vertexArraySize, indexArray, indexArraySize);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexArraySize * sizeof(float) * 8U, vertexArray, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8U, (void*)0);
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8U, (void*)12);
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8U, (void*)24);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glEnableVertexAttribArray(2U);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexArraySize, indexArray, GL_STATIC_DRAW);

	m_indexCount = indexArraySize;

	delete[] vertexArray;
	delete[] indexArray;
}

void MeshData::Unload()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);
	m_indexCount = 0U;
}

void MeshData::Render() const
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, (void*)0);
}
