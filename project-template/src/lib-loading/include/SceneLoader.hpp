#pragma once

#include <DGM/dgm.hpp>
#include <Scene.hpp>

class SceneLoader
{
    static inline const sf::FloatRect FULLSCREEN_VIEWPORT = {
        0.f, 0.f, 1.f, 1.f
    };

public:
    [[nodiscard]] static Scene
    loadScene(const dgm::ResourceManager&, const sf::Vector2f& baseResolution);
};