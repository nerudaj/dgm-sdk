#include "SceneLoader.hpp"

Scene SceneLoader::loadScene(
    const dgm::ResourceManager&,
    const sf::Vector2f& baseResolution,
    const Settings&)
{
    return Scene { .worldCamera =
                       dgm::Camera(FULLSCREEN_VIEWPORT, baseResolution),
                   .hudCamera =
                       dgm::Camera(FULLSCREEN_VIEWPORT, baseResolution) };
}