#include "cpp-anvil/anvil/coordinates.hpp"
#include "cpp-anvil/anvil/region.hpp"

namespace anvil {

Vec2 chunkRegion2ChunkWorld(Vec2 chunkCoord, Vec2 regionCoord)
{
    Vec2 worldCoords;
    worldCoords.x = regionCoord.x * Region::ChunksPerRegionAxis + chunkCoord.x;
    worldCoords.z = regionCoord.z * Region::ChunksPerRegionAxis + chunkCoord.z;
    return worldCoords;
}

Vec2 chunkWorld2ChunkRegion(Vec2 worldCoords)
{
    Vec2 regionCoords;
    regionCoords.x =
        (Region::ChunksPerRegionAxis + (worldCoords.x % Region::ChunksPerRegionAxis)) & 0x0000001F;
    regionCoords.z =
        (Region::ChunksPerRegionAxis + (worldCoords.z % Region::ChunksPerRegionAxis)) & 0x0000001F;

    return regionCoords;
}

} // namespace anvil
