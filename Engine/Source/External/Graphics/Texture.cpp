#include "Graphics/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>

using namespace Engine::Graphics;

Texture::Texture()
	:m_pRefCount(new unsigned int(1U)), m_pId(new unsigned int(0U))
{
}

Texture::Texture(const Texture& other)
	:m_pRefCount(other.m_pRefCount), m_pId(other.m_pId)
{
	(*m_pRefCount)++;
}

Texture::Texture(Texture&& other) noexcept
	:m_pRefCount(other.m_pRefCount), m_pId(other.m_pId)
{
	other.m_pRefCount = nullptr;
	other.m_pId = nullptr;
}

Texture& Texture::operator=(const Texture& other)
{
	if (this != &other)
	{
		(*m_pRefCount)--;

		if (*m_pRefCount == 0U)
		{
			glDeleteTextures(1, m_pId);
			delete m_pId;
			delete m_pRefCount;
		}

		m_pRefCount = other.m_pRefCount;
		m_pId = other.m_pId;
		(*m_pRefCount)++;
	}
	return *this;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)
	{
		(*m_pRefCount)--;

		if (*m_pRefCount == 0U)
		{
			glDeleteTextures(1, m_pId);
			delete m_pId;
			delete m_pRefCount;
		}

		m_pRefCount = other.m_pRefCount;
		m_pId = other.m_pId;

		other.m_pRefCount = nullptr;
		other.m_pId = nullptr;
	}

	return *this;
}

Texture::~Texture()
{
	if (m_pRefCount == nullptr)
		return;
	(*m_pRefCount)--;
	if (m_pRefCount == 0U)
	{
		glDeleteTextures(1, m_pId);
		delete m_pRefCount;
		delete m_pId;
	}
}

void Texture::Load(const char* filepath)
{
	glDeleteTextures(1, m_pId);

	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &width, &height, &numChannels, 0);

	if (data == nullptr)
		return;

	glGenTextures(1, m_pId);
	glBindTexture(GL_TEXTURE_2D, *m_pId);
	glTexImage2D(GL_TEXTURE_2D, 0, numChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, numChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::Use() const
{
	glBindTexture(GL_TEXTURE_2D, *m_pId);
}