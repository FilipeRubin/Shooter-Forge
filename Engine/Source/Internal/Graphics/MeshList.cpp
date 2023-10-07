#include "MeshList.hpp"
#include "Graphics/Mesh.hpp"
#include <cstring>

using namespace Engine::Graphics;

MeshList::MeshList()
	:m_array(nullptr), m_arraySize(0U)
{
}

MeshList::~MeshList()
{
	delete[] m_array;
}

void MeshList::Init(size_t arraySize)
{
	m_array = new Mesh*[arraySize] {nullptr};
	m_arraySize = arraySize;
}

unsigned int MeshList::AddMesh(Mesh* pMesh)
{
	for (size_t i = 0; i < m_arraySize; i++) // Find the first free slot (if there's one)
	{
		if (m_array[i] == nullptr)
		{
			m_array[i] = pMesh;
			return i;
		}
	}
	
	// If there's no free index
	const unsigned int oldSize = m_arraySize;
	ExpandArray();
	m_array[oldSize] = pMesh;
	return oldSize;
}

void MeshList::SetMesh(unsigned int index, Mesh* pMesh)
{
	m_array[index] = pMesh;
}

void MeshList::RemoveMesh(unsigned int index)
{
	m_array[index] = nullptr;
}

void MeshList::RenderAll()
{
	shader.Use();
	for (size_t i = 0; i < m_arraySize; i++)
	{
		if (m_array[i] == nullptr)
			continue;
		if (shader.IsDynamic())
			shader.SetModel(m_array[i]->transform);
		shader.SetMaterial(m_array[i]->material);
		m_array[i]->Render();
	}
}

void MeshList::ExpandArray()
{
	size_t newSize = m_arraySize * 2U; // Double the capacity
	Mesh** newArray = new Mesh*[newSize];
	memcpy(newArray, m_array, sizeof(Mesh*) * m_arraySize);
	delete[] m_array;
	m_array = newArray;
	m_arraySize = newSize;
}
