#include "cpp-anvil/nbt/types.hpp"

#include <array>

namespace anvil {

constexpr std::array<std::string_view, 14> TagTypeNames = {
    "End",       "Byte",   "Short", "Int",      "Long",     "Float",     "Double",
    "ByteArray", "String", "List",  "Compound", "IntArray", "LongArray", "Unknown"};

constexpr std::array<std::string_view, 14> TagNames = {
    "EndTag",      "ByteTag",     "ShortTag",     "IntTag",    "LongTag",
    "FloatTag",    "DoubleTag",   "ByteArrayTag", "StringTag", "ListTag",
    "CompoundTag", "IntArrayTag", "LongArrayTag", "UnknownTag"};

std::string_view getTagTypeName(TagType type)
{
    auto index = static_cast<unsigned char>(type);
    return index < TagTypeNames.size() ? TagTypeNames[index] : TagTypeNames.back();
}

std::string_view getTagName(TagType type)
{
    auto index = static_cast<unsigned char>(type);
    return index < TagNames.size() ? TagNames[index] : TagNames.back();
}

} // namespace anvil
