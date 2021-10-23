#pragma once

#include "GuiState.hpp"
#include "core/Settings.hpp"

class AppStateMenuOptions : public dgm::AppState, public GuiState {
protected:
	Settings &settings;

	void buildLayout();

public:
	virtual void input() override;
	virtual void update() override;
	virtual void draw() override;
	virtual [[nodiscard]] bool isTransparent() const noexcept override {
		return false;
	}

	AppStateMenuOptions(dgm::App& app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings);
};