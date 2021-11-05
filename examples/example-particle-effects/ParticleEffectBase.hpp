#pragma once

#include <DGM/dgm.hpp>

class ParticleEffectBase : public dgm::ps::ParticleSystemInterface {
public:
	float getRandomFloat(float min, float max) {
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}
};
