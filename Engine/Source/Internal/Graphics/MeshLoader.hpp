#pragma once
#include "Utilities/Vector2.hpp"
#include "Utilities/Vector3.hpp"

namespace Engine::Graphics
{
	class Mesh;
	class MeshLoader
	{
	public:
		static void LoadFromFile(const char* filePath, float*& out_vertexArray, size_t& out_vertexArraySize, unsigned int*& out_indexArray, size_t& out_indexArraySize);
	};
}