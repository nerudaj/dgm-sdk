#include <DGM/dgm.hpp>

#include <app/AppStateBootstrap.hpp>
//#include "Globals.hpp"

int main(int argc, char *argv[]) {
	std::string rootDir = "../resources";
	if (argc == 2) {
		rootDir = argv[1];
	}

	cfg::Ini ini;
	try {
		ini.loadFromFile(rootDir + "/app.ini");
	} catch (...) {}

	Settings settings;
	settings.loadFrom(ini);

	dgm::Window window(ini);
	dgm::App app(window);
	
	app.pushState<AppStateBootstrap>(rootDir, settings);
	app.run();

	window.close(ini);
	settings.saveTo(ini);

	ini.saveToFile(rootDir + "/app.ini");

	return 0;
}