#include "AppStatePaused.hpp"
#include "AppStateMenuOptions.hpp"
#include <array>
#include <utility>

template<class T>
requires std::is_arithmetic<T>::value
static std::string toLayout(T number) {
	assert(static_cast<T>(0) <= number || "Number is smaller than 0!");
	assert(number < static_cast<T>(100) || "Number is greated than 100");
	return std::to_string(number) + "%";
}

void AppStatePaused::buildLayout() {
	// Add new buttons and actions here
	typedef std::function<void(void)> CallbackType;
	typedef std::pair<std::string, CallbackType> PairType;
	const std::array<PairType, 3> BUTTON_PROPS = {
		PairType("Resume", [&] { app.popState(); }),
		PairType("Options", [&] { app.pushState<AppStateMenuOptions>(resmgr, audioPlayer, settings); }),
		PairType("Exit", [&] { app.exit(); })
	};

	// Following code builds the GUI
	constexpr unsigned BUTTON_COUNT = BUTTON_PROPS.size();
	constexpr float BUTTON_DISTANCE = 5.f;
	constexpr float BUTTON_HEIGHT = (100.f - (BUTTON_COUNT + 1) * BUTTON_DISTANCE) / BUTTON_COUNT;
	const tgui::Layout2d BUTTON_SIZE = { "90%", toLayout(BUTTON_HEIGHT) };

	auto createNestedButton = [&] (tgui::Panel::Ptr &target, const std::string& label, const unsigned yPosition, CallbackType callback) {
		auto btn = tgui::Button::create(label);
		btn->setSize(BUTTON_SIZE);
		btn->setPosition({
			toLayout(BUTTON_DISTANCE),
			toLayout(yPosition)
		});
		btn->connect("clicked", callback);
		btn->setTextSize(0);
		target->add(btn);
	};

	auto panel = tgui::Panel::create({ "20%", "50%" });
	panel->getRenderer()->setBackgroundColor(sf::Color(192, 192, 192));
	panel->setPosition({ "40%", "25%" });
	gui.add(panel);

	unsigned i = 0;
	for (auto&& [label, callback] : BUTTON_PROPS) {
		createNestedButton(panel, label, BUTTON_DISTANCE + i * (BUTTON_HEIGHT + BUTTON_DISTANCE), callback);
		i++;
	}
}

void AppStatePaused::input() {
	sf::Event event;
	while (app.window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			app.exit();
		} else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				app.popState();
			}
		}

		gui.handleEvent(event);
	}
}

AppStatePaused::AppStatePaused(dgm::App& app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings) : dgm::AppState(app), GuiState(resmgr, audioPlayer), settings(settings) {
	gui.setTarget(app.window.getWindowContext());
	buildLayout();
}
