#include "app/AppStateResourceLoader.hpp"
#include "app/AppStateMainMenu.hpp"
#include <algorithm>
#include <format>

void AppStateResourceLoader::input()
{
    app.pushState<AppStateMainMenu>(resmgr, audioPlayer, settings);
}

AppStateResourceLoader::AppStateResourceLoader(
    dgm::App& app, Settings& settings)
    : dgm::AppState(app), settings(settings)
{
    try
    {
        resmgr.loadResourceDir<sf::Texture>(
            settings.resourcesDir + "/graphics", { ".png" });
        resmgr.loadResourceDir<sf::Font>(
            settings.resourcesDir + "/fonts", { ".ttf" });
        resmgr.loadResourceDir<dgm::AnimationStates>(
            settings.resourcesDir + "/graphics", { ".json" });
        resmgr.loadResourceDir<sf::SoundBuffer>(
            settings.resourcesDir + "/sounds", { ".wav" });
    }
    catch (std::exception& e)
    {
        std::cerr << std::format(
            "error:AppStateResourceLoader: {}\n", e.what());
        throw;
    }

    audioPlayer.setSoundVolume(settings.soundVolume);
}
