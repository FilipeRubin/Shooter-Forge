#pragma once
#include "Utilities/Vector3.hpp"

namespace Engine::Physics
{
	class Simplex
	{
	public:
		Simplex();
		void Clear();
		void PushFront(const Utilities::Vector3& point);
		size_t GetSize() const;
		Utilities::Vector3& operator[](size_t index);
	private:
		Utilities::Vector3 m_points[4];
		size_t m_size;
	};
}