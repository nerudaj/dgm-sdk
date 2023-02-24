#include "app/AppStateIngame.hpp"
#include "app/AppStatePaused.hpp"
#include "events/EventQueue.hpp"

void AppStateIngame::setupViews()
{
	const sf::FloatRect FULL_SCREEN = { 0.f, 0.f, 1.f, 1.f };
	worldView.setViewport(FULL_SCREEN);
	worldView.setSize(sf::Vector2f(app.window.getSize()));

	hudView.setViewport(FULL_SCREEN);
	hudView.setSize(sf::Vector2f(app.window.getSize()));
	hudView.setCenter(sf::Vector2f(app.window.getSize()) / 2.f);
}

void AppStateIngame::input()
{
	sf::Event event;
	while (app.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			app.exit();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				app.pushState<AppStatePaused>(resmgr, audioPlayer, settings);
			}
		}
	}
}

void AppStateIngame::update()
{
	game.update(app.time);
}

void AppStateIngame::draw()
{
	// Rendering everything that is subject to world coordinate system
	app.window.getWindowContext().setView(worldView);
	renderer.renderWorldTo(app.window);

	// Rendering stuff that uses screen coordinates
	app.window.getWindowContext().setView(hudView);
	renderer.renderHudTo(app.window);
}

AppStateIngame::AppStateIngame(
	dgm::App& app,
	const dgm::ResourceManager& resmgr,
	Settings& settings,
	AudioPlayer& audioPlayer)
	: dgm::AppState(app)
	, resmgr(resmgr)
	, settings(settings)
	, audioPlayer(audioPlayer)
{
	setupViews();
}
