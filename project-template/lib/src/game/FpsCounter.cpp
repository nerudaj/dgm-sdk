#include "FpsCounter.hpp"

void FpsCounter::update(const float dt)
{
	displayText = std::to_string(
		static_cast<int>(1000.f / dt));
}