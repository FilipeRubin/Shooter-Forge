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
		Material();
		bool IsDiffuseEnabled() const;
	private:
		void UseTextures() const;
	};
}