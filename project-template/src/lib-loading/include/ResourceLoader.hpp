#pragma once

#include <DGM/dgm.hpp>
#include <LevelD.hpp>
#include <Scene.hpp>

class ResourceLoader
{
    static inline const sf::FloatRect FULLSCREEN_VIEWPORT = {
        0.f, 0.f, 1.f, 1.f
    };

public:
    static void loadResources(
        dgm::ResourceManager& resmgr, const std::filesystem::path& rootDir);

    [[nodiscard]] static dgm::Mesh
    loadMeshFromLevel(const LevelD& lvd, unsigned layerId = 0);
};
