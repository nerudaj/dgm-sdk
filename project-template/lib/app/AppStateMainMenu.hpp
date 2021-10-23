#pragma once

#include "GuiState.hpp"
#include "core/Settings.hpp"

class AppStateMainMenu : public dgm::AppState, public GuiState {
private:
	Settings &settings;
	bool viewShouldBeUpdated = true;

	void buildLayout();

public:
	virtual void input() override;
	virtual void update() override {}
	virtual void draw() override;
	virtual [[nodiscard]] bool isTransparent() const noexcept override {
		return false;
	}

	AppStateMainMenu(dgm::App &app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings);
};