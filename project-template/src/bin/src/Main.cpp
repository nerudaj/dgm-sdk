#include <Config.hpp>
#include <DGM/dgm.hpp>
#include <Settings.hpp>
#include <app/AppStateMainMenu.hpp>
#include <audio/AudioPlayer.hpp>
#include <settings/GameTitle.hpp>

int main(int argc, char* argv[])
{
    cfg::Args args("sr:");
    args.parse(argc, argv);

    Settings settings;
    if (args.isSet('r'))
        settings.resourcesDir = args.getArgumentValue('r').asString();
    settings.skipMainMenu = args.isSet('s');

    dgm::WindowSettings windowSettings = { .resolution =
                                               sf::Vector2u(1280, 720),
                                           .title = GAME_TITLE,
                                           .useFullscreen = false };

    const std::string CFG_FILE_PATH = "app.ini";

    // Load and process ini file
    cfg::Ini ini;
    try
    {
        ini.loadFromFile(CFG_FILE_PATH);

        windowSettings.resolution = sf::Vector2u(
            unsigned(ini["Window"].at("width").asInt()),
            unsigned(ini["Window"].at("height").asInt()));
        windowSettings.title = ini["Window"].at("title").asString();
        windowSettings.useFullscreen = ini["Window"].at("fullscreen").asBool();

        settings.soundVolume = ini["Audio"].at("soundVolume").asFloat();
        settings.musicVolume = ini["Audio"].at("musicVolume").asFloat();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Load resources
    dgm::JsonLoader jsonLoader;
    dgm::ResourceManager resmgr(jsonLoader);

    try
    {
        resmgr.loadResourceDir<sf::Texture>(
            (settings.resourcesDir / "graphics").string(), { ".png" });
        resmgr.loadResourceDir<sf::Font>(
            (settings.resourcesDir / "fonts").string(), { ".ttf" });
        resmgr.loadResourceDir<dgm::AnimationStates>(
            (settings.resourcesDir / "graphics").string(), { ".anim" });
        resmgr.loadResourceDir<dgm::Clip>(
            (settings.resourcesDir / "graphics").string(), { ".clip" });
        resmgr.loadResourceDir<sf::SoundBuffer>(
            (settings.resourcesDir / "sounds").string(), { ".wav" });
    }
    catch (std::exception& e)
    {
        std::cerr << std::format("error:Loading resources: {}\n", e.what());
        throw;
    }

    auto&& audioPlayer = AudioPlayer(CHANNEL_COUNT, resmgr);

    // Launch application
    dgm::Window window(windowSettings);
    dgm::App app(window);

    app.pushState<AppStateMainMenu>(resmgr, audioPlayer, settings);
    app.run();

    auto outWindowSettings = window.close();

    // Update configuration file
    cfg::Ini outCfg;
    outCfg["Window"]["width"] = int(outWindowSettings.resolution.x);
    outCfg["Window"]["height"] = int(outWindowSettings.resolution.y);
    outCfg["Window"]["fullscreen"] = outWindowSettings.useFullscreen;
    outCfg["Window"]["title"] = outWindowSettings.title;

    outCfg["Audio"]["soundVolume"] = settings.soundVolume;
    outCfg["Audio"]["musicVolume"] = settings.musicVolume;

    outCfg.saveToFile(CFG_FILE_PATH);

    return 0;
}