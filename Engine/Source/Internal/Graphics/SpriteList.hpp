#pragma once
#include "CanvasShader.hpp"

namespace Engine::Graphics
{
	class Sprite;
	class SpriteList
	{
	public:
		CanvasShader shader;
		SpriteList();
		~SpriteList();
		void Init(size_t arraySize);
		unsigned int AddSprite(Sprite* pSprite);
		void SetSprite(unsigned int index, Sprite* pSprite);
		void RemoveSprite(unsigned int index);
		void RenderAll();
		SpriteList(const SpriteList&) = delete;
		SpriteList& operator=(const SpriteList&) = delete;
	private:
		Sprite** m_array; // Does NOT own the elements it points to
		size_t m_arraySize;
		void ExpandArray();
	};
}