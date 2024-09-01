#ifndef CPP_ANVIL_ANVIL_COORDINATES_HPP 
#define CPP_ANVIL_ANVIL_COORDINATES_HPP 

// STL
#include <cstdint>

namespace anvil {

struct Vec2
{
    int32_t x;
    int32_t z;
};

struct Vec3
{
    int32_t x;
    int32_t z;
    int32_t y;
};

Vec2 chunkRegion2ChunkWorld(Vec2 chunkCoord, Vec2 regionCoord);
Vec2 chunkWorld2ChunkRegion(Vec2 worldWoord);

} // namespace anvil

#endif // CPP_ANVIL_ANVIL_COORDINATES_HPP 