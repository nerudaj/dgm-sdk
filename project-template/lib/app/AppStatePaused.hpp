#pragma once

#include "GuiState.hpp"
#include "core/Settings.hpp"

class AppStatePaused : public dgm::AppState, public GuiState {
protected:
	Settings& settings;

	void buildLayout();

public:
	virtual void input() override;
	virtual void update() override {}
	virtual void draw() override { gui.draw(); }
	virtual [[nodiscard]] bool isTransparent() const noexcept override {
		return true;
	}
	virtual void restoreFocus() override {
		// View has to be update
		gui.setView(app.window.getWindowContext().getView());
	}

	AppStatePaused(dgm::App& app, const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer, Settings& settings);
};