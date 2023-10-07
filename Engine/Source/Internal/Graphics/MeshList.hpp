#pragma once
#include "WorldShader.hpp"

// class MeshList
//
// Purpose: Store an array of world entities and render them using the RenderAll() methods

namespace Engine::Graphics
{
	class Mesh;
	class MeshList
	{
	public:
		WorldShader shader;
		MeshList();
		~MeshList();
		void Init(size_t arraySize);
		unsigned int AddMesh(Mesh* pMesh);
		void SetMesh(unsigned int index, Mesh* pMesh);
		void RemoveMesh(unsigned int index);
		void RenderAll();
		MeshList(const MeshList&)            = delete;
		MeshList& operator=(const MeshList&) = delete;
	private:
		Mesh** m_array; // Does NOT own the elements it points to
		size_t m_arraySize;
		void ExpandArray();
	};
}