#include "SpriteList.hpp"
#include "Graphics/Sprite.hpp"
#include <vcruntime_string.h>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

SpriteList::SpriteList() :
	m_array(nullptr),
	m_arraySize(0U)
{
}

SpriteList::~SpriteList()
{
	delete[] m_array;
}

void SpriteList::Init(size_t arraySize)
{
	m_array = new Sprite*[arraySize] {nullptr};
	m_arraySize = arraySize;
}

unsigned int SpriteList::AddSprite(Sprite* pSprite)
{
	for (size_t i = 0; i < m_arraySize; i++) // Find the first free slot (if there's one)
	{
		if (m_array[i] == nullptr)
		{
			m_array[i] = pSprite;
			return i;
		}
	}

	// If there's no free index
	const unsigned int oldSize = m_arraySize;
	ExpandArray();
	m_array[oldSize] = pSprite;
	return oldSize;
}

void SpriteList::SetSprite(unsigned int index, Sprite* pSprite)
{
	m_array[index] = pSprite;
}

void SpriteList::RemoveSprite(unsigned int index)
{
	m_array[index] = nullptr;
}

void SpriteList::RenderAll()
{
	shader.Use();
	for (size_t i = 0; i < m_arraySize; i++)
	{
		if (m_array[i] == nullptr)
			continue;
		shader.SetTexture(m_array[i]->texture);
		shader.SetScreenAnchor(m_array[i]->screenAnchor);
		shader.SetSize(m_array[i]->size);
		shader.SetPosition(m_array[i]->position);
		shader.SetRotation(m_array[i]->rotation);
		m_array[i]->Render();
	}
}

void SpriteList::ExpandArray()
{
	size_t newSize = m_arraySize * 2U; // Double the capacity
	Sprite** newArray = new Sprite*[newSize];
	memcpy(newArray, m_array, sizeof(Sprite*) * m_arraySize);
	memset(newArray + m_arraySize, (int)nullptr, sizeof(Sprite*) * m_arraySize);
	delete[] m_array;
	m_array = newArray;
	m_arraySize = newSize;
}
