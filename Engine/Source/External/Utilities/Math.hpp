#pragma once

namespace Engine::Utilities
{
	class Math
	{
	public:
		static constexpr float PI = 3.1415927f;
		static constexpr float HALF_PI = PI * 0.5f;
		static constexpr float DOUBLE_PI = PI * 2.0f;
		static float Lerp(const float& from, const float& to, const float& t);
		static float RandomFloat(const float& min, const float& max);
	};
}