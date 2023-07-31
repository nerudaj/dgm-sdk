#pragma once

#include <DGM/dgm.hpp>
#include <LevelD.hpp>

class Builder
{
public:
    [[nodiscard]] static dgm::Mesh
    buildMeshFromLvd(const LevelD& lvd, unsigned layerId = 0);

    template<dgm::UniversalReference<dgm::Clip> _Clip>
    [[nodiscard]] static dgm::TileMap buildTileMapFromLvd(
        const sf::Texture& texture,
        const _Clip&& clip,
        const LevelD& lvd,
        unsigned layerId = 0)
    {
        auto&& result = dgm::TileMap(texture, std::forward<_Clip>(clip));
        result.build(
            { lvd.mesh.tileWidth, lvd.mesh.tileHeight },
            lvd.mesh.layers.at(layerId).tiles,
            { lvd.mesh.layerWidth, lvd.mesh.layerHeight });
        return result;
    }
};