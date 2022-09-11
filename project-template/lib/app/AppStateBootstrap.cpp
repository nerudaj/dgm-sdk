#include "AppStateBootstrap.hpp"
#include "AppStateMainMenu.hpp"

void AppStateBootstrap::input() {
	app.pushState<AppStateMainMenu>(resmgr, audioPlayer, settings, skipToGame);
}

AppStateBootstrap::AppStateBootstrap(dgm::App& app, const std::string root, Settings& settings, bool skipToGame) : dgm::AppState(app), rootDir(root), settings(settings), skipToGame(skipToGame) {
	try {
		resmgr.loadResourceDir<sf::Texture>(rootDir + "/graphics/textures");
		resmgr.loadResourceDir<sf::Font>(rootDir + "/graphics/fonts");
		resmgr.loadResourceDir<std::shared_ptr<dgm::AnimationStates>>(rootDir + "/graphics/configs");
		resmgr.loadResourceDir<sf::SoundBuffer>(rootDir + "/audio/sounds");
	}
	catch (std::exception& e) {
		std::cerr << "error:AppStateMainMenu: " << e.what() << std::endl;
		throw;
	}

	audioPlayer.setSoundVolume(settings.soundVolume);
}
