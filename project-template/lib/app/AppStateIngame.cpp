#include "AppStateIngame.hpp"

void AppStateIngame::input() {
	sf::Event event;
	while (app.window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				app.popState();
			}
			else if (event.key.code == sf::Keyboard::B) {
				audioPlayer.playSoundOnChannel("bounce.wav", 0);
			}
			else if (event.key.code == sf::Keyboard::K) {
				audioPlayer.playSoundOnChannel("kick.wav", 1);
			}
			else if (event.key.code == sf::Keyboard::A) {
				actor.setAnimationState("run-left");
			}
			else if (event.key.code == sf::Keyboard::D) {
				actor.setAnimationState("run-right");
			}
			else if (event.key.code == sf::Keyboard::F2) {
				//app->pushState(new AppStateShell(resmgr, settings));
			}
		}
	}
}

void AppStateIngame::update() {
	actor.update(app.time);
}

void AppStateIngame::draw() {
	app.window.beginDraw();

	app.window.draw(text);
	actor.draw(app.window);

	app.window.endDraw();
}

AppStateIngame::AppStateIngame(dgm::App& app, const dgm::ResourceManager& resmgr, Settings& settings, AudioPlayer& audioPlayer) : dgm::AppState(app), resmgr(resmgr), settings(settings), audioPlayer(audioPlayer) {
	text.setFont(resmgr.get<sf::Font>("cruft.ttf"));
	text.setString("Press B to play bounce.wav, press K to play kick.wav\n"
		"Press A to toggle run left animation\n"
		"Press D to toggle run right animation\n"
		"Press ESC to return to Main menu\n"
		"Press F2 to access console");
	text.setFillColor(sf::Color::White);

	actor.setTexture(resmgr.get<sf::Texture>("sample_texture.png"));
	actor.setAnimationStates(resmgr.get <std::shared_ptr<dgm::AnimationStates>>("sample_config.json"));
}
