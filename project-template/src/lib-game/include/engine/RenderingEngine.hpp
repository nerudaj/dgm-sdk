#pragma once

#include "core/Scene.hpp"
#include "render/FpsCounter.hpp"
#include "render/RenderContext.hpp"
#include <DGM/DGM.hpp>
#include <events/EventQueue.hpp>
#include <events/RenderingEvents.hpp>

import Memory;

class RenderingEngine final
{
public:
    [[nodiscard]] RenderingEngine(
        mem::Rc<const dgm::ResourceManager> resmgr,
        mem::Rc<EventQueue> eventQueue,
        Scene& scene);

public: // Must visit on all related events
    constexpr inline void operator()(const EventToggleFpsRequested&) noexcept
    {
        showFps = !showFps;
    }

public:
    void update(const dgm::Time& time);

    void renderWorldTo(dgm::Window& window);

    void renderHudTo(dgm::Window& window);

private:
    mem::Rc<const dgm::ResourceManager> resmgr;
    mem::Rc<EventQueue> eventQueue;
    Scene& scene;
    bool showFps = true;
    FpsCounter fpsCounter;
    RenderContext context;
};
