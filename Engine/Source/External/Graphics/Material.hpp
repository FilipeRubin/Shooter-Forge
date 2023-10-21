#pragma once
#include "Utilities/Vector3.hpp"
#include "Texture.hpp"

namespace Engine::Graphics
{
	class Material
	{
		friend class WorldShader;
	public:
		Utilities::Vector3 diffuseColor;
		Texture            diffuseTexture;
		Utilities::Vector3 specularColor;
		Texture            specularTexture;
		Utilities::Vector3 emissionColor;
		Texture            emissionTexture;
		Material();
		bool IsDiffuseTextureEnabled() const;
		bool IsSpecularTextureEnabled() const;
		bool IsEmissionTextureEnabled() const;
	private:
		void UseTextures() const;
	};
}