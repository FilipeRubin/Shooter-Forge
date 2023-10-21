#include "Graphics/Material.hpp"
#include <glad/glad.h>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

Material::Material() :
	diffuseColor(Vector3(1.0f, 1.0f, 1.0f)),
	specularColor(Vector3(1.0f, 1.0f, 1.0f)),
	emissionColor(Vector3(0.0f, 0.0f, 0.0f))
{
}

bool Material::IsDiffuseTextureEnabled() const
{
	return diffuseTexture.m_pId != nullptr and *diffuseTexture.m_pId != 0U;
}

bool Material::IsSpecularTextureEnabled() const
{
	return specularTexture.m_pId != nullptr and *specularTexture.m_pId != 0U;
}

bool Material::IsEmissionTextureEnabled() const
{
	return emissionTexture.m_pId != nullptr and *emissionTexture.m_pId != 0U;
}

void Material::UseTextures() const
{
	glActiveTexture(GL_TEXTURE0);
	diffuseTexture.Use();
	glActiveTexture(GL_TEXTURE1);
	specularTexture.Use();
	glActiveTexture(GL_TEXTURE2);
	emissionTexture.Use();
}
