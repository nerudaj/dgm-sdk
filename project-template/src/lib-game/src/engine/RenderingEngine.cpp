#include "engine/RenderingEngine.hpp"

RenderingEngine::RenderingEngine(
    mem::Rc<const dgm::ResourceManager> _resmgr,
    mem::Rc<EventQueue> eventQueue,
    Scene& scene)
    : resmgr(_resmgr)
    , eventQueue(eventQueue)
    , scene(scene)
    , context(RenderContext::buildRenderContext(*resmgr))
{
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
