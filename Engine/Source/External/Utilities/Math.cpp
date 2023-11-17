#include "Utilities/Math.hpp"
#include <cmath>

using namespace Engine::Utilities;

float Math::Lerp(const float& from, const float& to, const float& weight)
{
	return from + (to - from) * weight;
}

float Math::RandomFloat(const float& min, const float& max)
{
	float sortedNumber = (float)rand() / (float)RAND_MAX;

	return min + sortedNumber * (max - min);
}
