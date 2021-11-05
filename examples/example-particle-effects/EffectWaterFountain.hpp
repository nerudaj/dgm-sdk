#pragma once

#include "ParticleEffectBase.hpp"

class EffectWaterFountain : public ParticleEffectBase {
protected:
	const float MIN_LIFESPAN = 2.f; // in seconds
	const float MAX_LIFESPAN = 4.f; // in seconds
	const float MIN_EMITTED_SPREAD = 1.f;
	const float MAX_EMITTER_SPREAD = 5.f; // degrees
	const sf::Time SPAWN_TIMEOUT = sf::seconds(0.01f);
	const float EMITTER_FORCE = 320.f;
	const sf::Vector2f GRAVITY_FORCE = sf::Vector2f(0.f, 160.f);

	sf::Vector2f emitterPosition;
	sf::Time spawnTimer = sf::Time::Zero;

protected:
	static float getRandomlyNegatedOne() {
		return (rand() % 2 ? 1.f : -1.f);
	}

	void spawnParticle() {
		// If buffer of particles doesn't have any unused slot, back out
		if (!particles.expand()) return;

		const float randomLifespan = getRandomFloat(MIN_LIFESPAN, MAX_LIFESPAN);
		const float randomAngle = getRandomFloat(MIN_EMITTED_SPREAD, MAX_EMITTER_SPREAD) * getRandomlyNegatedOne();
		const sf::Vector2f randomForward = dgm::Math::rotateVector(sf::Vector2f(0.f, -1.f), randomAngle) * EMITTER_FORCE;
		
		// expand() allocated new slot at the end of the buffer
		auto& p = particles.last();
		p->spawn(emitterPosition, sf::Vector2f(1.f, 1.f) * randomLifespan, sf::seconds(randomLifespan));
		p->setForward(randomForward);
		p->setColor(sf::Color::Cyan);
	}

public:
	virtual void update(const dgm::Time& time) {
		const auto DELTA_GRAVITY = GRAVITY_FORCE * time.getDeltaTime();

		for (unsigned i = 0; i < particles.size(); i++) {
			auto& p = particles[i];
			
			const auto fwd = p->getForward() * time.getDeltaTime();
			p->moveForwardBy(fwd);
			p->setForward(p->getForward() + DELTA_GRAVITY);
			p->updateLifespan(time.getElapsed());

			// If lifespan timed out
			if (not p->isAlive()) {
				// TODO: replace with p->despawn();
				p->spawn(emitterPosition, { 0.f, 0.f }, sf::Time::Zero);

				// Removal means swapping with last valid slot so we need to repeat iteration on this index
				particles.remove(i--);
			}
		}

		spawnTimer += time.getElapsed();
		if (spawnTimer > SPAWN_TIMEOUT) {
			spawnTimer = sf::Time::Zero;
			spawnParticle();
		}
	}

	EffectWaterFountain(const sf::Vector2f& emitterPosition) : emitterPosition(emitterPosition) {}
};