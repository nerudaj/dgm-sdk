#include <DGM/dgm.hpp>
#include <settings/GameTitle.hpp>
#include <Config.hpp>

#include <app/AppStateResourceLoader.hpp>

int main(int argc, char* argv[])
{
	cfg::Args args("sr:");
	args.parse(argc, argv);

	Settings settings;
	if (args.isSet('r'))
		settings.resourcesDir = args.getArgumentValue('r').asString();
	settings.skipMainMenu = args.isSet('s');

	dgm::WindowSettings windowSettings = {
		.resolution = sf::Vector2u(1280, 720),
		.title = GAME_TITLE,
		.useFullscreen = false
	};

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

	// Launch application
	dgm::Window window(windowSettings);
	dgm::App app(window);

	app.pushState<AppStateResourceLoader>(settings);
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