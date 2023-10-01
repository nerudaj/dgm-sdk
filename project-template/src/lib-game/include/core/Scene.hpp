#pragma once

#include <DGM/dgm.hpp>
#include <Settings.hpp>
#include <entt/entt.hpp>

// Add all game actors and objects to this struct as it is passed
// between all engines and automatically created in AppStateIngame
// using buildScene function
// After adding actors here, you might want to update render/RenderContext.hpp
// with objects required to render your actors
struct Scene
{
    dgm::Camera worldCamera;
    dgm::Camera hudCamera;

    static Scene buildScene(
        const dgm::ResourceManager& resmgr,
        const sf::Vector2f& baseResolution,
        const Settings& settings);
};