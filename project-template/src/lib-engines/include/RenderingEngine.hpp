#pragma once

#include "RenderingEvents.hpp"
#include <DGM/DGM.hpp>

class RenderingEngine final
{
public: // Must visit on all related events
    void operator()(const DummyRenderingEvent& e) {}

public:
    void update(const dgm::Time& time);

    void renderWorldTo(dgm::Window& window);

    void renderHudTo(dgm::Window& window);
};
