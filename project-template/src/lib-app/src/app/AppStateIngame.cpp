#include "app/AppStateIngame.hpp"
#include "EventQueue.hpp"
#include "app/AppStatePaused.hpp"
#include <SceneLoader.hpp>

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
    EventQueue::processEvents<AudioEvent>(audioEngine);
    EventQueue::processEvents<PhysicsEvent>(physicsEngine);
    EventQueue::processEvents<GameEvent>(gameRulesEngine);
    EventQueue::processEvents<RenderingEvent>(renderingEngine);
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
    dgm::App& app,
    mem::Rc<const dgm::ResourceManager> resmgr,
    mem::Rc<GuiWrapper> gui,
    mem::Rc<Settings> settings,
    mem::Rc<AudioPlayer> audioPlayer)
    : dgm::AppState(app)
    , resmgr(resmgr)
    , gui(gui)
    , settings(settings)
    , audioPlayer(audioPlayer)
    , GAME_RESOLUTION(sf::Vector2f(app.window.getSize()))
    , scene(SceneLoader::loadScene(*resmgr, GAME_RESOLUTION))
    , audioEngine(resmgr, audioPlayer)
    , gameRulesEngine(scene)
    , physicsEngine(scene)
    , renderingEngine(resmgr, scene)
{
    scene.worldCamera.setPosition(GAME_RESOLUTION / 2.f);
    scene.hudCamera.setPosition(GAME_RESOLUTION / 2.f);
}
