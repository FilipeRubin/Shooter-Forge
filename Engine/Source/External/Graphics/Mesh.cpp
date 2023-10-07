#include "Graphics/Mesh.hpp"
#include "Graphics/MeshLoader.hpp"
#include "Graphics/MeshData.hpp"
#include "Graphics/Renderer.hpp"
#include <glad/glad.h>
#include <fstream>

using namespace Engine::Graphics;
using namespace Engine::Utilities;

Mesh::Mesh() :
	m_isInArray(false),
	m_arrayIndex(0U),
	m_pRefCount(new unsigned int(1)),
	m_pData(new MeshData())
{
}

Mesh::Mesh(const Mesh& other) :
	m_isInArray(false),
	m_arrayIndex(0U),
	m_pRefCount(other.m_pRefCount),
	m_pData(other.m_pData)
{
	(*m_pRefCount)++;
	if (other.m_isInArray)
		Renderer::AddMesh(m_parameters.isDynamic, this);
}

Mesh::Mesh(Mesh&& other) noexcept :
	m_isInArray(other.m_isInArray),
	transform(other.transform),
	m_arrayIndex(other.m_arrayIndex),
	m_pRefCount(other.m_pRefCount),
	m_pData(other.m_pData)
{
	if (other.m_isInArray)
		Renderer::SetMesh(m_parameters.isDynamic, other.m_arrayIndex, this); // Transfer the slot reserved in the array to the new instance
	else
		m_arrayIndex = 0U;
	other.m_arrayIndex = 0U;
	other.m_pRefCount = nullptr;
	other.m_pData = nullptr;
}

Mesh::~Mesh()
{
	if (m_pRefCount == nullptr) // If hollow object
		return;
	if (m_isInArray)
		Renderer::RemoveMesh(m_parameters.isDynamic, m_arrayIndex);
	(*m_pRefCount)--;
	if (*m_pRefCount == 0U)
	{
		delete m_pRefCount;
		delete m_pData;
	}
}

Mesh& Mesh::operator=(const Mesh& other) // Copy (and share) only the data, nothing else
{
	if (this != &other) // If not other
	{
		if (m_isInArray)
		{
			Renderer::RemoveMesh(m_parameters.isDynamic, m_arrayIndex);
		}
		if (other.m_isInArray)
		{
			m_arrayIndex = Renderer::AddMesh(m_parameters.isDynamic, this);
			m_isInArray = true;
		}
		else
		{
			m_isInArray = false;
		}

		(*m_pRefCount)--;
		if (*m_pRefCount == 0)
		{
			delete m_pRefCount;
			delete m_pData;
		}
		m_pRefCount = other.m_pRefCount;
		m_pData = other.m_pData;
		(*m_pRefCount)++;
	}
	return *this;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept // Other gets "hollowed"
{
	if (this != &other) // If not other
	{
		if (m_isInArray)
			Renderer::RemoveMesh(m_parameters.isDynamic, m_arrayIndex);
		if (other.m_isInArray)
			Renderer::SetMesh(other.m_parameters.isDynamic, other.m_arrayIndex, this);

		(*m_pRefCount)--;
		if (*m_pRefCount == 0)
		{
			delete m_pRefCount;
			delete m_pData;
		}
		m_pRefCount = other.m_pRefCount;
		m_pData = other.m_pData;
		m_parameters = other.m_parameters;

		other.m_pRefCount = nullptr;
		other.m_pData = nullptr;
	}
	return *this;
}

void Mesh::Load(const char* filePath, Parameters params)
{
	if (m_pData != nullptr)
	{
		m_parameters = params;
		m_pData->Load(filePath);
		m_arrayIndex = Renderer::AddMesh(m_parameters.isDynamic, this);
		m_isInArray = true;
	}
}

void Mesh::Render()
{
	m_pData->Render();
}
