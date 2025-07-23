#include "cpp-anvil/nbt/types.hpp"

namespace anvil {

const char * TagTypeNames[14] = {
    "End",
    "Byte",
    "Short",
    "Int",
    "Long",
    "Float",
    "Double",
    "ByteArray",
    "String",
    "List",
    "Compound",
    "IntArray",
    "LongArray",
    "Unknown"
};

const char * TagNames[14] = {
    "EndTag",
    "ByteTag",
    "ShortTag",
    "IntTag",
    "LongTag",
    "FloatTag",
    "DoubleTag",
    "ByteArrayTag",
    "StringTag",
    "ListTag",
    "CompoundTag",
    "IntArrayTag",
    "LongArrayTag",
    "UnknownTag"
};

std::string_view getTagTypeName(TagType type)
{
    if(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray)) {
        return TagTypeNames[static_cast<unsigned char>(type)];
    } else {
        return TagTypeNames[13];
    }
}

std::string_view getTagName(TagType type)
{
    if(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray)) {
        return TagNames[static_cast<unsigned char>(type)];
    } else {
        return TagNames[13];
    }
}

} // namespace anvil
