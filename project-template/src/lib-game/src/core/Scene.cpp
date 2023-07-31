#include "core/Scene.hpp"

static inline const sf::FloatRect FULLSCREEN_VIEWPORT = { 0.f, 0.f, 1.f, 1.f };

Scene Scene::buildScene(
    const dgm::ResourceManager&,
    const sf::Vector2f& baseResolution,
    const Settings& settings)
{
    return Scene { .worldCamera =
                       dgm::Camera(FULLSCREEN_VIEWPORT, baseResolution),
                   .hudCamera =
                       dgm::Camera(FULLSCREEN_VIEWPORT, baseResolution) };
}
