#include <DGM/dgm.hpp>
#include "../ResourceDir.hpp"
#include "ParticleEffectBase.hpp"
#include "EffectWaterFountain.hpp"
#include "EffectBloodSpatter.hpp"

int main() {
	srand(time(nullptr));

	dgm::Window window({1600, 900}, "Example: Particle Effects", false);
	dgm::Time time;

	const float FIRST_ROW_Y_BOTTOM = 435.f;
	const float SECOND_ROW_Y_BOTTOM = 870.f;

	sf::RectangleShape border;
	border.setOutlineThickness(3.f);
	border.setOutlineColor(sf::Color::White);
	border.setFillColor(sf::Color::Transparent);
	border.setSize({ 350.f, 405.f });

	EffectWaterFountain effectFountain({ 200.f, FIRST_ROW_Y_BOTTOM });
	effectFountain.init(256);

	EffectBloodSpatter effectBloodSpatter({600.f, 200.f}, FIRST_ROW_Y_BOTTOM );
	effectBloodSpatter.init(64);

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		/* LOGIC */
		time.reset();

		effectFountain.update(time);
		effectBloodSpatter.update(time);
		
		/* DRAW */
		window.beginDraw();

		effectFountain.draw(window);
		effectBloodSpatter.draw(window);

		for (unsigned y = 0; y < 2; y++) {
			for (unsigned x = 0; x < 4; x++) {
				border.setPosition(40.f + x * (40.f + 350.f), 30.f + y * (30.f + 405.f));
				window.draw(border);
			}
		}

		window.endDraw();
	}

	return 0;
}