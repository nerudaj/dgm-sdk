#pragma once

#include "ParticleEffectBase.hpp"

auto toUnit(const sf::Vector2f& vec) noexcept {
	return vec == sf::Vector2f(0.f, 0.f) ? vec : vec / dgm::Math::vectorSize(vec);
}

class EffectBloodSpatter : public ParticleEffectBase {
protected:
	// Effect parameters
	const float EMITTER_RADIUS = 15.f;
	const float MIN_EMITTER_FORCE = 10.f;
	const float MAX_EMITTER_FORCE = 200.f;
	const float MIN_PARTICLE_SIZE = 5.f;
	const float MAX_PARTICLE_SIZE = 10.f;
	const sf::Vector2f GRAVITY = { 0.f, 500.f };
	const sf::Time LIFESPAN = sf::seconds(2.f);

	// Initialized by ctor
	const sf::Vector2f emitterPosition;
	const float floorY;

	// Vars
	sf::Time lifespan;

public:
	virtual void init(const std::size_t particleCount) override {
		ParticleEffectBase::init(particleCount);

		// This effect initializes all particles at once
		// We need to loop over all allocated slots and "add" them to visible part of the buffer
		for (unsigned i = 0; i < particles.capacity(); i++) {
			particles.expand();
		}

		reset();
	}

	virtual void update(const dgm::Time& time) override {
		const auto DELTA_GRAVITY = GRAVITY * time.getDeltaTime();

		for (auto& p : particles) {
			if (p->getPosition().y < floorY) {
				const auto DELTA_FORWARD = p->getForward() * time.getDeltaTime();
				p->moveForwardBy(DELTA_FORWARD);
				p->setForward(p->getForward() + DELTA_GRAVITY);
			}
		}

		// Normally we would like to destroy the effect once finishes
		// in this example we let it restart and loop forever
		lifespan -= time.getElapsed();
	}

	void reset() {
		lifespan = LIFESPAN;

		for (auto& p : particles) {
			const float randomSizeFactor = getRandomFloat(MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE);
			const float randomForwardFactor = getRandomFloat(MIN_EMITTER_FORCE, MAX_EMITTER_FORCE);
			const float randomSpawnOffset = getRandomFloat(0.f, EMITTER_RADIUS);
			const auto randomUnitVector = toUnit(sf::Vector2f(
				getRandomFloat(-1.f, 1.f), getRandomFloat(-1.f, 1.f)
			));

			p->setColor(sf::Color::Red);
			p->setForward(randomUnitVector * randomForwardFactor);
			p->setForward({ p->getForward().x / 1.5f, p->getForward().y });

			// We don't care about lifespan of individual particles in this effect, so it can be zero
			p->spawn(emitterPosition + randomUnitVector * randomSpawnOffset, sf::Vector2f(1.f, 1.f) * randomSizeFactor, sf::Time::Zero);
		}
	}

	[[nodiscard]] bool finished() const noexcept {
		return lifespan <= sf::Time::Zero;
	}

	EffectBloodSpatter(const sf::Vector2f &position, const float floorYCoord) : emitterPosition(position), floorY(floorYCoord) {}
};