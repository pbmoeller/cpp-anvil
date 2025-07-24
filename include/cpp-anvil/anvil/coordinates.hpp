#ifndef CPP_ANVIL_ANVIL_COORDINATES_HPP 
#define CPP_ANVIL_ANVIL_COORDINATES_HPP 

#include <cstdint>

namespace anvil {

//! @brief struct used for 2 dimensional integer coordinates, i.e. chunk coodinates.
struct Vec2
{
    int32_t x;
    int32_t z;
};

//! @brief struct used for 3 dimensional integer coordinates, i.e. block coodinates.
struct Vec3
{
    int32_t x;
    int32_t z;
    int32_t y;
};

//! @brief Converts chunk coordinates from region system to world system.
//! @param chunkCoord Region coordinates of chunk.
//! @param regionCoord Region coordinates in the world.
//! @return Chunk coordinates in world system.
Vec2 chunkRegion2ChunkWorld(Vec2 chunkCoord, Vec2 regionCoord);

//! @brief Converts chunk coordinates from world system to region system.
//! @param worldWoord World coordinates of chunk.
//! @return Chunk coordinates in region system.
Vec2 chunkWorld2ChunkRegion(Vec2 worldWoord);

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_COORDINATES_HPP
