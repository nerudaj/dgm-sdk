#include <Config.hpp>
#include <DGM/dgm.hpp>
#include <Settings.hpp>
#include <app/AppStateMainMenu.hpp>
#include <app/GuiWrapper.hpp>
#include <audio/AudioPlayer.hpp>
#include <cxxopts.hpp>
#include <settings/GameTitle.hpp>

import Memory;

// Takes std::expected and throws exception if it contains error
#define THROW_ON_ERROR(expr)                                                   \
    if (auto&& result = expr; !result) throw std::runtime_error(result.error());

CmdSettings processCmdParameters(int argc, char* argv[])
{
    cxxopts::Options options("MyProgram", "One line description of MyProgram");
    // clang-format off
    options.add_options()
        ("s,skip-menu", "Start game directly")
        ("r,resource-dir", "Path to resources", cxxopts::value<std::string>());
    // clang-format on
    auto args = options.parse(argc, argv);

    CmdSettings result;

    if (args.count("skip-menu") > 0)
        result.skipMainMenu = args["skip-menu"].as<bool>();
    if (args.count("resource-dir") > 0)
        result.resourcesDir = args["resource-dir"].as<std::string>();

    return result;
}

AppSettings loadAppSettings(const std::filesystem::path& path)
{
    try
    {
        return loadFromFile(path);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return AppSettings {};
}

void loadResources(
    dgm::ResourceManager& resmgr, const std::filesystem::path& rootDir)
{
    dgm::JsonLoader jsonLoader;

    try
    {
        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<sf::Texture>(
            rootDir / "graphics",
            [](const std::filesystem::path& path, sf::Texture& texture)
            { texture.loadFromFile(path.string()); },
            { ".png" }));

        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<sf::Font>(
            rootDir / "fonts",
            [](const std::filesystem::path& path, sf::Font& font)
            { font.loadFromFile(path.string()); },
            { ".ttf" }));

        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<tgui::Font>(
            rootDir / "fonts",
            [](const std::filesystem::path& path, tgui::Font& font)
            { font = tgui::Font(path.string()); },
            { ".ttf" }));

        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<dgm::AnimationStates>(
            rootDir / "graphics",
            [&jsonLoader](
                const std::filesystem::path& path,
                dgm::AnimationStates& animStates)
            { animStates = jsonLoader.loadAnimationsFromFile(path); },
            { ".anim" }));

        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<dgm::Clip>(
            rootDir / "graphics",
            [&jsonLoader](const std::filesystem::path& path, dgm::Clip& clip)
            { clip = jsonLoader.loadClipFromFile(path); },
            { ".clip" }));

        THROW_ON_ERROR(resmgr.loadResourcesFromDirectory<sf::SoundBuffer>(
            rootDir / "sounds",
            [&jsonLoader](
                const std::filesystem::path& path, sf::SoundBuffer& buffer)
            { buffer.loadFromFile(path.string()); },
            { ".wav" }));
    }
    catch (std::exception& e)
    {
        std::cerr << std::format("error:Loading resources: {}\n", e.what());
        throw;
    }
}

int main(int argc, char* argv[])
{
    const auto CONFIG_FILE_PATH = "app.json";

    auto&& settings = mem::Rc<Settings>();
    settings->cmdSettings = processCmdParameters(argc, argv);
    settings->appSettings = loadAppSettings(CONFIG_FILE_PATH);

    dgm::WindowSettings windowSettings = {
        .resolution = sf::Vector2u(
            settings->appSettings.windowWidth,
            settings->appSettings.windowHeight),
        .title = GAME_TITLE,
        .useFullscreen = settings->appSettings.fullscreen
    };

    dgm::Window window(windowSettings);
    dgm::App app(window);
    auto&& gui = mem::Rc<GuiWrapper>(window.getWindowContext());
    auto&& resmgr = mem::Rc<dgm::ResourceManager>();
    auto&& audioPlayer = mem::Rc<AudioPlayer>(CHANNEL_COUNT, resmgr);

    loadResources(*resmgr, settings->cmdSettings.resourcesDir);
    gui->get().setFont(resmgr->get<tgui::Font>("cruft.ttf").value());

    app.pushState<AppStateMainMenu>(resmgr, gui, audioPlayer, settings);
    app.run();

    auto outWindowSettings = window.close();

    // Update configuration file
    settings->appSettings.windowWidth = outWindowSettings.resolution.x;
    settings->appSettings.windowHeight = outWindowSettings.resolution.y;
    settings->appSettings.fullscreen = outWindowSettings.useFullscreen;
    saveToFile(CONFIG_FILE_PATH, settings->appSettings);

    return 0;
}