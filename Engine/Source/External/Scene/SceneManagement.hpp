#pragma once
#include "SceneBase.hpp"

namespace Engine::Scene
{
	class SceneManagement // Maybe change this to a simple static class instead of a singleton (?)
	{
	private:
		friend class Core;

		static SceneManagement s_instance;

		SceneBase* m_pCurrentScene;
		SceneManagement();
		SceneManagement(const SceneManagement&) = delete;
		SceneManagement(SceneManagement&&) = delete;

		static void Render();
		static void Cleanup();
	public:
		static void SetScene(SceneBase*&& pScene);
	};
}