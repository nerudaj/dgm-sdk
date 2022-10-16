#pragma once

#include <DGM/dgm.hpp>
#include "core/Settings.hpp"
#include "core/AudioPlayer.hpp"

class AppStateBootstrap : public dgm::AppState
{
private:
	Settings& settings;
	dgm::JsonLoader loader;
	dgm::ResourceManager resmgr = dgm::ResourceManager(loader);
	AudioPlayer audioPlayer = AudioPlayer(CHANNEL_COUNT, resmgr);

public:
	virtual void input() override;
	virtual void update() override {}
	virtual void draw() override {}
	virtual [[nodiscard]] bool isTransparent() const noexcept override
	{
		return false;
	}

	AppStateBootstrap(dgm::App& app, Settings& settings);
};