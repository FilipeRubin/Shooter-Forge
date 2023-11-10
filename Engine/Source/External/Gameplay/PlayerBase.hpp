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
		friend class Scene::SceneManagement;
	public:
		static void SetActivePlayer(PlayerBase* pPlayer = nullptr);
		Utilities::Transform transform;
		PlayerBase();
		virtual ~PlayerBase();
	private:
		static PlayerBase* s_activePlayer;
		bool m_initialized;
		virtual void Init();
		virtual void Process();
	};
}