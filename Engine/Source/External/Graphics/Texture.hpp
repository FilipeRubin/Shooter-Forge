#pragma once

// class Texture
//
// Purpose: Be a high-level abstraction for OpenGL textures. Its private members can be accessed from Material.

namespace Engine::Graphics
{
	class Texture
	{
		friend class Material;
	public:
		Texture();
		Texture(const Texture& other);
		Texture(Texture&& other) noexcept;
		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other) noexcept;
		~Texture();
		void Load(const char* filepath);
		void SetFilter(bool value) const;
	private:
		unsigned int* m_pRefCount;
		unsigned int* m_pId; // Texture ID stored into the GPU
		void Use() const;
	};
}