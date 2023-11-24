#pragma once
#include "SceneBase.hpp"

namespace Engine::Scene
{
	class SceneManagement // Maybe change this to a simple static class instead of a singleton (?)
	{
		friend class Core;
	public:
		static void SetScene(SceneBase*&& pScene);
	private:
		static SceneManagement s_instance;

		SceneBase* m_pCurrentScene;
		SceneBase* m_pNextScene;
		SceneManagement();
		SceneManagement(const SceneManagement&) = delete;
		SceneManagement(SceneManagement&&) = delete;

		static bool HasNextScene();
		static void LoadNextScene();
		static void Render();
		static void Cleanup();
	};
}