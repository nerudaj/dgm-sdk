#include <DGM/dgm.hpp>

#include <app/AppStateBootstrap.hpp>

int main(int argc, char *argv[]) {
	cfg::Args args("sr:");
	args.parse(argc, argv);
	bool skipToGame = args.isSet('s');
	std::string rootDir = args.isSet('r')
		? args.getArgumentValue('r').asString()
		: "../resources";

	cfg::Ini ini;
	try {
		ini.loadFromFile("app.ini");
	} catch (...) {
		ini["Window"]["width"] = 1280;
		ini["Window"]["height"] = 720;
		ini["Window"]["fullscreen"] = false;
		ini["Window"]["title"] = "Example";
	}

	Settings settings;
	settings.loadFrom(ini);

	dgm::Window window(ini);
	dgm::App app(window);
	
	app.pushState<AppStateBootstrap>(rootDir, settings, skipToGame);
	app.run();

	window.close(ini);
	settings.saveTo(ini);

	ini.saveToFile("app.ini");

	return 0;
}