#pragma once
#include "Utilities/Transform.hpp"
#include "Material.hpp"

// class Mesh
//
// Purpose: Provide base functionality to load meshes.

namespace Engine::Graphics
{
	class MeshData;
	class Mesh
	{
		friend class Renderer;
		friend class MeshList;
	public:
		struct Parameters // Parameters affect both how the model will be stored in memory and how it will be rendered.
		{
			bool isDynamic = true;
		};

		Utilities::Transform transform;
		Graphics::Material material;
		Mesh();                                 // Constructor
		Mesh(const Mesh& other);                // Copy constructor
		Mesh(Mesh&& other) noexcept;            // Move constructor
		virtual ~Mesh();                        // Destructor
		Mesh& operator=(const Mesh& other);     // Copy assignment operator
		Mesh& operator=(Mesh&& other) noexcept; // Move assignment operator
		
		void Load(const char* filePath, Parameters params = Parameters());
	private:
		Parameters    m_parameters;
		bool          m_isInArray;  // If this is inside an array
		unsigned int  m_arrayIndex; // Unique per instance, not shared
		unsigned int* m_pRefCount;
		MeshData*     m_pData;
		void Render();
	};
}