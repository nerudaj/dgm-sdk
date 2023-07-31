#include "utils/Builder.hpp"

dgm::Mesh Builder::buildMeshFromLvd(const LevelD& lvd, unsigned layerId)
{
    return dgm::Mesh(
        lvd.mesh.layers.at(layerId).blocks,
        { lvd.mesh.layerWidth, lvd.mesh.layerHeight },
        { lvd.mesh.tileWidth, lvd.mesh.tileHeight });
}
