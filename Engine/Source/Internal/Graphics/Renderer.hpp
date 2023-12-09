#pragma once
#include "Utilities/Vector2.hpp"
#include "MeshList.hpp"
#include "SpriteList.hpp"

// static class Renderer
//
// Purpose: Store instances of MeshList and render them according to the pipeline. Handle basic rendering properties.

namespace Engine::Graphics
{
	class Renderer
	{
	public:
		static Utilities::Vector2 windowSize;
		static void Init(size_t arraySize);
		static void RenderAll();
		static unsigned int AddMesh(bool isDynamic, Mesh* pMesh);
		static void SetMesh(bool isDynamic, unsigned int index, Mesh* pMesh); // Called in the move constructor of Mesh
		static void RemoveMesh(bool isDynamic, unsigned int index);
		static unsigned int AddSprite(Sprite* pSprite);
		static void RemoveSprite(unsigned int index);
	private:
		static MeshList s_dynamicMeshes;
		static MeshList s_staticMeshes;
		static SpriteList s_sprites;
	};
}