#include "cpp-anvil/nbt/basic_tag.hpp"
#include "cpp-anvil/nbt/collection_tag.hpp"
#include "cpp-anvil/nbt/compound_tag.hpp"
#include "cpp-anvil/nbt/list_tag.hpp"
#include "cpp-anvil/nbt/primitive_tag.hpp"

namespace anvil {

EndTag* BasicTag::asEndTag()
{
    return tag_cast<EndTag*>(this);
}

PrimitiveTag<ByteType, TagType::Byte>* BasicTag::asByteTag()
{
    return tag_cast<PrimitiveTag<ByteType, TagType::Byte>*>(this);
}

PrimitiveTag<ShortType, TagType::Short>* BasicTag::asShortTag()
{
    return tag_cast<PrimitiveTag<ShortType, TagType::Short>*>(this);
}

 PrimitiveTag<IntType, TagType::Int>* BasicTag::asIntTag()
{
    return tag_cast<PrimitiveTag<IntType, TagType::Int>*>(this);
}

PrimitiveTag<LongType, TagType::Long>* BasicTag::asLongTag()
{
    return tag_cast<PrimitiveTag<LongType, TagType::Long>*>(this);
}

PrimitiveTag<FloatType, TagType::Float>* BasicTag::asFloatTag()
{
    return tag_cast<PrimitiveTag<FloatType, TagType::Float>*>(this);
}

PrimitiveTag<DoubleType, TagType::Double>* BasicTag::asDoubleTag()
{
    return tag_cast<PrimitiveTag<DoubleType, TagType::Double>*>(this);
}

CollectionTag<ByteType, TagType::ByteArray>* BasicTag::asByteArrayTag()
{
    return tag_cast<CollectionTag<ByteType, TagType::ByteArray>*>(this);
}

PrimitiveTag<StringType, TagType::String>* BasicTag::asStringTag()
{
    return tag_cast<PrimitiveTag<StringType, TagType::String>*>(this);
}

CollectionTag<IntType, TagType::IntArray>* BasicTag::asIntArrayTag()
{
    return tag_cast<CollectionTag<IntType, TagType::IntArray>*>(this);
}

CollectionTag<LongType, TagType::LongArray>* BasicTag::asLongArrayTag()
{
    return tag_cast<CollectionTag<LongType, TagType::LongArray>*>(this);
}

ListTag* BasicTag::asListTag()
{
    return tag_cast<ListTag*>(this);
}

CompoundTag* BasicTag::asCompoundTag()
{
    return tag_cast<CompoundTag*>(this);
}

} // namespace anvil
