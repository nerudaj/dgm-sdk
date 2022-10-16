#include "AppStateBootstrap.hpp"
#include "AppStateMainMenu.hpp"
#include <format>
#include <algorithm>

void AppStateBootstrap::input()
{
	app.pushState<AppStateMainMenu>(resmgr, audioPlayer, settings);
}

AppStateBootstrap::AppStateBootstrap(
	dgm::App& app,
	Settings& settings)
	:
	dgm::AppState(app),
	settings(settings)
{
	try
	{
		resmgr.loadResourceDir<sf::Texture>(settings.resourcesDir + "/graphics/textures", { ".png" });
		resmgr.loadResourceDir<sf::Font>(settings.resourcesDir + "/graphics/fonts", { ".ttf" });
		resmgr.loadResourceDir<dgm::AnimationStates>(settings.resourcesDir + "/graphics/configs", { ".json" });
		resmgr.loadResourceDir<sf::SoundBuffer>(settings.resourcesDir + "/audio/sounds", { ".wav" });
	}
	catch (std::exception& e)
	{
		std::cerr << std::format("error:AppStateBootstrap: {}\n", e.what());
		throw;
	}

	audioPlayer.setSoundVolume(settings.soundVolume);
}
