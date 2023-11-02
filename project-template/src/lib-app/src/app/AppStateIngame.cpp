#include "app/AppStateIngame.hpp"
#include "app/AppStatePaused.hpp"
#include <events/EventQueue.hpp>

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
                app.pushState<AppStatePaused>(gui, audioPlayer, settings);
            }
        }
    }
}

void AppStateIngame::update()
{
    audioEngine.update(app.time);
    physicsEngine.update(app.time);
    gameRulesEngine.update(app.time);
    renderingEngine.update(app.time);

    // At the end of each update, process the event queue
    eventQueue->processAndClear(gameRulesEngine);
    eventQueue->processAndClear(renderingEngine);
}

void AppStateIngame::draw()
{
    // Rendering everything that is subject to world coordinate system
    app.window.getWindowContext().setView(scene.worldCamera.getCurrentView());
    renderingEngine.renderWorldTo(app.window);

    // Rendering stuff that uses screen coordinates
    app.window.getWindowContext().setView(scene.hudCamera.getCurrentView());
    renderingEngine.renderHudTo(app.window);
}

AppStateIngame::AppStateIngame(
    dgm::App& _app,
    mem::Rc<const dgm::ResourceManager> _resmgr,
    mem::Rc<tgui::Gui> _gui,
    mem::Rc<Settings> _settings,
    mem::Rc<AudioPlayer> _audioPlayer)
    : dgm::AppState(_app)
    , resmgr(_resmgr)
    , gui(_gui)
    , settings(_settings)
    , audioPlayer(_audioPlayer)
    , GAME_RESOLUTION(sf::Vector2f(app.window.getSize()))
    , scene(Scene::buildScene(*resmgr, GAME_RESOLUTION, *settings))
    , audioEngine(resmgr, audioPlayer)
    , gameRulesEngine(scene, eventQueue)
    , physicsEngine(scene)
    , renderingEngine(resmgr, eventQueue, scene)
{
    scene.worldCamera.setPosition(GAME_RESOLUTION / 2.f);
    scene.hudCamera.setPosition(GAME_RESOLUTION / 2.f);
}
