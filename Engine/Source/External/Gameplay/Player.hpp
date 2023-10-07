#pragma once
#include "Graphics/Camera.hpp"
#include "PlayerBase.hpp"

namespace Engine::Gameplay
{
	class Player : public PlayerBase
	{
	public:
		Graphics::Camera camera;
	private:
		Utilities::Vector3 m_velocity;

		void Init() override;
		void Process() override;

		inline void ProcessMovement();
		inline void ProcessMouseLook();
	};
}