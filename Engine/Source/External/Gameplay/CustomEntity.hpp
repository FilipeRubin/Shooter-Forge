#pragma once
#include "Utilities/Transform.hpp"

namespace Engine::Gameplay
{
	class CustomEntity
	{
	public:
		Utilities::Transform transform;
	public:
		CustomEntity();
		virtual void Process();
		virtual ~CustomEntity();
	};
}