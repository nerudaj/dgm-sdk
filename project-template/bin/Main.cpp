#include <DGM/dgm.hpp>
#include <core/GameTitle.hpp>

#include <app/AppStateBootstrap.hpp>

int main(int argc, char* argv[])
{
	cfg::Args args("sr:");
	args.parse(argc, argv);

	Settings settings;
	if (args.isSet('r'))
		settings.resourcesDir = args.getArgumentValue('r').asString();
	settings.skipMainMenu = args.isSet('s');

	cfg::Ini ini;
	try
	{
		ini.loadFromFile("app.ini");
	}
	catch (...)
	{
		ini["Window"]["width"] = 1280;
		ini["Window"]["height"] = 720;
		ini["Window"]["fullscreen"] = false;
		ini["Window"]["title"] = GAME_TITLE;
	}

	if (ini.hasSection("Audio") && ini["Audio"].hasKey("soundVolume"))
		settings.soundVolume = ini["Audio"].at("soundVolume").asFloat();
	if (ini.hasSection("Audio") && ini["Audio"].hasKey("musicVolume"))
		settings.musicVolume = ini["Audio"].at("musicVolume").asFloat();

	dgm::Window window(ini);
	dgm::App app(window);

	app.pushState<AppStateBootstrap>(settings);
	app.run();

	window.close(ini);

	ini["Audio"]["soundVolume"] = settings.soundVolume;
	ini["Audio"]["musicVolume"] = settings.musicVolume;

	ini.saveToFile("app.ini");

	return 0;
}