#pragma once

namespace Engine::Scene
{
	class SceneBase
	{
	private:
		friend class SceneManagement;
		virtual void Init() = 0;
		virtual void Render() = 0;
	public:
		SceneBase();
		SceneBase(const SceneBase& other) = delete;
		SceneBase(SceneBase&& other) = delete;
		SceneBase operator=(const SceneBase& other) = delete;
		virtual ~SceneBase();
	};
}