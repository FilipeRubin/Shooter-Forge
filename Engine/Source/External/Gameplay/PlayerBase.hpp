#pragma once
#include "Utilities/Transform.hpp"

namespace Engine::Scene
{
	class SceneManagement;
}

namespace Engine::Gameplay
{
	class PlayerBase
	{
	private:
		friend class Scene::SceneManagement;
		static PlayerBase* s_activePlayer;
	public:
		static void SetActivePlayer(PlayerBase* pPlayer = nullptr);
	private:
		bool m_initialized;
	public:
		Utilities::Transform transform;
	private:
		virtual void Init();
		virtual void Process();
	public:
		PlayerBase();
		virtual ~PlayerBase();
	};
}