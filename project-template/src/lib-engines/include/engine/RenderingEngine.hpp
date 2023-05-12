#pragma once

#include "RenderingEvents.hpp"
#include "Scene.hpp"
#include "render/FpsCounter.hpp"
#include "render/RenderContext.hpp"
#include <DGM/DGM.hpp>

class RenderingEngine final
{
public:
    [[nodiscard]] RenderingEngine(
        const dgm::ResourceManager& resmgr, Scene& scene);

public: // Must visit on all related events
    constexpr void operator()(const EventToggleFpsRequested& e) noexcept
    {
        showFps = !showFps;
    }

public:
    void update(const dgm::Time& time);

    void renderWorldTo(dgm::Window& window);

    void renderHudTo(dgm::Window& window);

private:
    const dgm::ResourceManager& resmgr;
    Scene& scene;
    bool showFps = true;
    FpsCounter fpsCounter;
    RenderContext context;
};
