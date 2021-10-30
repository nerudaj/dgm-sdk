#include "app/AppStateMainMenu.hpp"
#include "app/AppStateMenuOptions.hpp"
#include "app/AppStateIngame.hpp"

void AppStateMainMenu::buildLayout() {
	auto title = createOptionLabel({ "0%", "5%" }, { "100%", "25%" }, "Project Title");
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->setTextSize(72);
	gui.add(title);

	createButton("Play", { "42.5%", "35%" }, { "15%", "5%" }, [this]() {
		app.pushState<AppStateIngame>(resmgr, settings, audioPlayer);
	});
	createButton("Options", { "42.5%", "41%" }, { "15%", "5%" }, [this]() {
		app.pushState<AppStateMenuOptions>(resmgr, audioPlayer, settings);
	});
	createButton("Exit", { "42.5%", "47%" }, { "15%", "5%" }, [this] () {
		app.exit();
	});
}

void AppStateMainMenu::input() {
	sf::Event event;
	while (app.window.pollEvent(event)) {
		gui.handleEvent(event);
	}
}

AppStateMainMenu::AppStateMainMenu(dgm::App& app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings) : dgm::AppState(app), GuiState(resmgr, audioPlayer), settings(settings) {
	gui.setTarget(app.window.getWindowContext());
	buildLayout();
}