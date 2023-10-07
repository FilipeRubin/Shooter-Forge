#pragma once

namespace Engine::Utilities
{
	class Time
	{
	private:
		friend class Core;
		static float s_deltaTime;
		static float s_time;
		static void UpdateDeltaTime(float time);
	public:
		static const float& GetDeltaTime();
		static const float& GetTime();
	};
}