#pragma once

namespace Engine::Utilities
{
	struct Vector3;
}

namespace Engine::Physics
{
	class ColliderLoader
	{
	public:
		static void LoadFromFile(const char* filePath, const Utilities::Vector3*& out_pointsArray, size_t& out_pointsArraySize);
	};
}