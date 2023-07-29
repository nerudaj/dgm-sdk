#include "engine/RenderingEngine.hpp"

RenderingEngine::RenderingEngine(
    mem::Rc<const dgm::ResourceManager> resmgr, Scene& scene)
    : resmgr(resmgr), scene(scene)
{
    context.text.setFont(resmgr->get<sf::Font>("cruft.ttf").value());
    context.text.setFillColor(sf::Color::White);
    context.text.setCharacterSize(32);
}

void RenderingEngine::update(const dgm::Time& time)
{
    fpsCounter.update(time.getDeltaTime());
}

void RenderingEngine::renderWorldTo(dgm::Window&) {}

void RenderingEngine::renderHudTo(dgm::Window& window)
{
    context.text.setString(fpsCounter.getText());
    window.draw(context.text);
}
