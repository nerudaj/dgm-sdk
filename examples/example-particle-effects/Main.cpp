#include <DGM/dgm.hpp>
#include "../ResourceDir.hpp"
#include "ParticleEffectBase.hpp"
#include "EffectWaterFountain.hpp"

int main() {
	srand(time(nullptr));

	dgm::Window window({1600, 900}, "Example: Particle Effects", false);
	dgm::Time time;

	sf::RectangleShape border;
	border.setOutlineThickness(3.f);
	border.setOutlineColor(sf::Color::White);
	border.setFillColor(sf::Color::Black);
	border.setSize({ 350.f, 405.f });

	EffectWaterFountain effectFountain({ 200.f, 400.f });
	effectFountain.init(256);

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
		
		/* DRAW */
		window.beginDraw();

		for (unsigned y = 0; y < 2; y++) {
			for (unsigned x = 0; x < 4; x++) {
				border.setPosition(40.f + x * (40.f + 350.f), 30.f + y *(30.f + 405.f));
				window.draw(border);
			}
		}

		effectFountain.draw(window);

		window.endDraw();
	}

	return 0;
}