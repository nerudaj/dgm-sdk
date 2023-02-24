#pragma once

#include <DGM\dgm.hpp>
#include "core/Settings.hpp"
#include "events/Events.hpp"
#include "game/Game.hpp"
#include "game/Renderer.hpp"

class AppStateIngame final : public dgm::AppState
{
public:
	AppStateIngame(
		dgm::App& app,
		const dgm::ResourceManager& resmgr,
		Settings& settings,
		AudioPlayer& audioPlayer);

public:
	virtual void input() override;
	virtual void update() override;
	virtual void draw() override;
	virtual [[nodiscard]] bool isTransparent() const noexcept override
	{
		return false;
	}

	virtual void restoreFocus() override
	{
		setupViews();
	}


protected:
	void setupViews();

protected:
	const dgm::ResourceManager& resmgr;
	Settings& settings;
	AudioPlayer& audioPlayer;

	sf::View worldView, hudView;
	dgm::Camera camera = dgm::Camera(worldView);

	Game game = Game(
		camera,
		audioPlayer);
	Renderer renderer = Renderer(
		resmgr,
		game);
};