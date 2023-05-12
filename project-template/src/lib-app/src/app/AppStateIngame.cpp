#include "app/AppStateIngame.hpp"
#include "app/AppStatePaused.hpp"

// #include "events/EventQueue.hpp"

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
    // game.update(app.time);

    // At the end of each update, process the event queue
    // EventQueue::process(eventProcessor);
}

void AppStateIngame::draw()
{
    // Rendering everything that is subject to world coordinate system
    app.window.getWindowContext().setView(worldCamera.getCurrentView());
    // renderer.renderWorldTo(app.window);

    // Rendering stuff that uses screen coordinates
    app.window.getWindowContext().setView(hudCamera.getCurrentView());
    // renderer.renderHudTo(app.window);
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
    , GAME_RESOLUTION(sf::Vector2f(app.window.getSize()))
    , worldCamera(FULLSCREEN_VIEWPORT, GAME_RESOLUTION)
    , hudCamera(FULLSCREEN_VIEWPORT, GAME_RESOLUTION)
{
    worldCamera.setPosition(GAME_RESOLUTION / 2.f);
    hudCamera.setPosition(GAME_RESOLUTION / 2.f);
}
