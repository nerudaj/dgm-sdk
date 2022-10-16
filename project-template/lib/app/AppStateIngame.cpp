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
			else if (event.key.code == sf::Keyboard::B)
			{
				EventQueue::add<EventPlaySound>("bounce.wav", 0, false);
			}
			else if (event.key.code == sf::Keyboard::K)
			{
				EventQueue::add<EventPlaySound>("kick.wav", 0, false);
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				actor.setAnimationState("run-left");
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				actor.setAnimationState("run-right");
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				camera.shake(sf::seconds(1.f), 20.f);
			}
		}
	}
}

void AppStateIngame::update()
{
	actor.update(app.time);

	camera.setPosition(actor.getPosition());
	camera.update(app.time);

	// At the end of each update, process the event queue
	EventQueue::process(eventProcessor);
}

void AppStateIngame::draw()
{
	// Rendering everything that is subject to world coordinate system
	app.window.getWindowContext().setView(worldView);
	actor.draw(app.window);
	app.window.draw(text);

	// Rendering stuff that uses screen coordinates
	app.window.getWindowContext().setView(hudView);

	// Display FPS counter only in DEBUG mode
#ifdef _DEBUG
	fpsCounterText.setString(std::to_string(static_cast<int>(1000.f / app.time.getDeltaTime())));
	fpsCounterText.setPosition(app.window.getSize().x - 20.f - fpsCounterText.getGlobalBounds().width, 20.f);
	app.window.draw(fpsCounterText);
#endif // _DEBUG
}

AppStateIngame::AppStateIngame(dgm::App& app, const dgm::ResourceManager& resmgr, Settings& settings, AudioPlayer& audioPlayer) : dgm::AppState(app), resmgr(resmgr), settings(settings), audioPlayer(audioPlayer)
{
	setupViews();

	text.setFont(resmgr.get<sf::Font>("cruft.ttf"));
	text.setString("Press B to play bounce.wav, press K to play kick.wav\n"
		"Press A to toggle run left animation\n"
		"Press D to toggle run right animation\n"
		"Press S to shake camera\n"
		"Press ESC to return to Main menu");
	text.setFillColor(sf::Color::White);

#ifdef _DEBUG
	fpsCounterText.setFont(resmgr.get<sf::Font>("cruft.ttf"));
	fpsCounterText.setFillColor(sf::Color::White);
	fpsCounterText.setOutlineColor(sf::Color::Black);
	fpsCounterText.setOutlineThickness(1.f);
	fpsCounterText.setCharacterSize(60);
#endif

	actor.setTexture(resmgr.get<sf::Texture>("sample_texture.png"));
	actor.setAnimationStates(resmgr.get<dgm::AnimationStates>("sample_config.json"));
}
