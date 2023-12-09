#pragma once
#include "Texture.hpp"
#include "Utilities/Vector2.hpp"

namespace Engine::Graphics
{
	class Sprite
	{
		friend class Core;
	public:
		Texture texture;
		Utilities::Vector2 screenAnchor;
		Utilities::Vector2 size;
		Utilities::Vector2 position;
		float rotation;
		Sprite();
		~Sprite();
		void Render() const;
	private:
		unsigned int m_index;
		static unsigned int s_vbo;
		static unsigned int s_vao;
		static void Init();
		static void Cleanup();
	};
}