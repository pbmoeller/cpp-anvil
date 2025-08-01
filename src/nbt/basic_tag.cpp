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

const EndTag* BasicTag::asEndTag() const
{
    return tag_cast<const EndTag*>(this);
}

const PrimitiveTag<ByteType, TagType::Byte>* BasicTag::asByteTag() const
{
    return tag_cast<const PrimitiveTag<ByteType, TagType::Byte>*>(this);
}

const PrimitiveTag<ShortType, TagType::Short>* BasicTag::asShortTag() const
{
    return tag_cast<const PrimitiveTag<ShortType, TagType::Short>*>(this);
}

const PrimitiveTag<IntType, TagType::Int>* BasicTag::asIntTag() const
{
    return tag_cast<const PrimitiveTag<IntType, TagType::Int>*>(this);
}

const PrimitiveTag<LongType, TagType::Long>* BasicTag::asLongTag() const
{
    return tag_cast<const PrimitiveTag<LongType, TagType::Long>*>(this);
}

const PrimitiveTag<FloatType, TagType::Float>* BasicTag::asFloatTag() const
{
    return tag_cast<const PrimitiveTag<FloatType, TagType::Float>*>(this);
}

const PrimitiveTag<DoubleType, TagType::Double>* BasicTag::asDoubleTag() const
{
    return tag_cast<const PrimitiveTag<DoubleType, TagType::Double>*>(this);
}

const CollectionTag<ByteType, TagType::ByteArray>* BasicTag::asByteArrayTag() const
{
    return tag_cast<const CollectionTag<ByteType, TagType::ByteArray>*>(this);
}

const PrimitiveTag<StringType, TagType::String>* BasicTag::asStringTag() const
{
    return tag_cast<const PrimitiveTag<StringType, TagType::String>*>(this);
}

const CollectionTag<IntType, TagType::IntArray>* BasicTag::asIntArrayTag() const
{
    return tag_cast<const CollectionTag<IntType, TagType::IntArray>*>(this);
}

const CollectionTag<LongType, TagType::LongArray>* BasicTag::asLongArrayTag() const
{
    return tag_cast<const CollectionTag<LongType, TagType::LongArray>*>(this);
}

const ListTag* BasicTag::asListTag() const
{
    return tag_cast<const ListTag*>(this);
}

const CompoundTag* BasicTag::asCompoundTag() const
{
    return tag_cast<const CompoundTag*>(this);
}

} // namespace anvil
