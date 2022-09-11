#pragma once

#include "GuiState.hpp"
#include "core/Settings.hpp"

class AppStateMainMenu : public dgm::AppState, public GuiState {
private:
	Settings &settings;
	bool skipToGame = false;

	void buildLayout();

public:
	virtual void input() override;
	virtual void update() override {}
	virtual void draw() override { gui.draw(); }
	virtual [[nodiscard]] bool isTransparent() const noexcept override {
		return false;
	}
	virtual [[nodiscard]] sf::Color getClearColor() const override {
		return sf::Color::White;
	}
	virtual void restoreFocus() override {
		// View has to be update
		gui.setView(app.window.getWindowContext().getView());
	}

	AppStateMainMenu(dgm::App &app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings, bool skipToGame);
};