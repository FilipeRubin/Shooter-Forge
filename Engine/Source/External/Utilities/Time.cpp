#include "Utilities/Time.hpp"

using namespace Engine::Utilities;

float Time::s_deltaTime = 0.0f;
float Time::s_time = 0.0f;

void Time::UpdateDeltaTime(float time)
{
	s_time = time;
	static float lastTime = time;

	s_deltaTime = time - lastTime;

	lastTime = time;
}

const float& Time::GetDeltaTime()
{
	return s_deltaTime;
}

const float& Time::GetTime()
{
	return s_time;
}
