#pragma once

// class MeshData
//
// Purpose: Store OpenGL buffer id's and make sure to keep an unique copy of it.

namespace Engine::Graphics
{
	class MeshData
	{
	public:
		MeshData();
		MeshData(MeshData&& other) noexcept;
		~MeshData();
		MeshData& operator=(MeshData&& other) noexcept;

		void Load(const char* filePath);
		void Unload();
		void Render() const;

		MeshData(const MeshData& other)            = delete;
		MeshData& operator=(const MeshData& other) = delete;
	private:
		unsigned int m_vbo;
		unsigned int m_vao;
		unsigned int m_ebo;
		unsigned int m_indexCount;
	};
}