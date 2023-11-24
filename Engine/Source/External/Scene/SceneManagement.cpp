#include "Scene/SceneManagement.hpp"
#include "Gameplay/PlayerBase.hpp"

using namespace Engine::Gameplay;
using namespace Engine::Scene;

SceneManagement SceneManagement::s_instance = SceneManagement();

SceneManagement::SceneManagement()
	:m_pCurrentScene(nullptr), m_pNextScene(nullptr)
{
}

bool SceneManagement::HasNextScene()
{
	return s_instance.m_pNextScene;
}

void SceneManagement::LoadNextScene()
{
	// Free up the currently loaded scene (if there's one)
	if (s_instance.m_pCurrentScene != nullptr)
		delete s_instance.m_pCurrentScene;

	// Assign the pointer to the next one
	s_instance.m_pCurrentScene = s_instance.m_pNextScene;
	s_instance.m_pNextScene = nullptr;

	// If the new scene is not nullptr, it'll initialize it
	if (s_instance.m_pCurrentScene != nullptr)
		s_instance.m_pCurrentScene->Init();
}

void SceneManagement::Render()
{
	if (s_instance.m_pCurrentScene != nullptr)
	{
		if (PlayerBase::s_activePlayer != nullptr)
		{
			PlayerBase::s_activePlayer->Process();
		}
		s_instance.m_pCurrentScene->Render();
	}
}

void SceneManagement::Cleanup()
{
	// Literally clean up the memory
	if (s_instance.m_pCurrentScene != nullptr)
	{
		delete s_instance.m_pCurrentScene;
		s_instance.m_pCurrentScene = nullptr;
	}
}

void SceneManagement::SetScene(SceneBase*&& pScene)
{
	s_instance.m_pNextScene = pScene;

	// Set the input pointer to null
	if (pScene != nullptr)
		pScene = nullptr;
}