#pragma once

#include <DGM/dgm.hpp>

// Struct that should contain all primitives needed to render
// the Scene.
// Automatically constructed by the RenderingEngine using the
// buildRenderContext method
struct RenderContext
{
    sf::Text text;

    [[nodiscard]] static RenderContext
    buildRenderContext(const dgm::ResourceManager& resmgr);
};
