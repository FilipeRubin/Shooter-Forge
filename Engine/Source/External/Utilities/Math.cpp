#include "Utilities/Math.hpp"

using namespace Engine::Utilities;

float Math::Lerp(const float& from, const float& to, const float& weight)
{
	return from + (to - from) * weight;
}
