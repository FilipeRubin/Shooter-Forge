#include "Graphics/Material.hpp"
#include <glad/glad.h>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

Material::Material()
	:diffuseColor(Vector3(1.0f, 1.0f, 1.0f))
{
}

bool Material::IsDiffuseEnabled() const
{
	return diffuseTexture.m_pId != nullptr and *diffuseTexture.m_pId != 0U;
}

void Material::UseTextures() const
{
	glActiveTexture(GL_TEXTURE0);
	diffuseTexture.Use();
	//glActiveTexture(GL_TEXTURE1);
	//specularTexture.Use();
}
