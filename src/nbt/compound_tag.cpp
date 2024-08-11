// cpp-avil
#include <cpp-anvil/nbt/compound_tag.hpp>

namespace nbt {

bool CompoundTag::hasChild(const std::string &name) const
{
    for(const auto &tag : m_value) {
        if(tag->name() == name) {
            return true;
        }
    }
    return false;
}

BasicTag* CompoundTag::getChildByName(const std::string &name)
{
    for(const auto &tag : m_value) {
        if(tag->name() == name) {
            return tag.get();
        }
    }
    return nullptr;
}

const BasicTag* CompoundTag::getChildByName(const std::string &name) const
{
    for(const auto &tag : m_value) {
        if(tag->name() == name) {
            return tag.get();
        }
    }
    return nullptr;
}

bool CompoundTag::push_back(std::unique_ptr<CompoundType> value) {
    if(value) {
        m_value.push_back(std::move(value));
        return true;
    }
    return false;
}

bool CompoundTag::push_back(CompoundType *value) {
    if(value) {
        m_value.push_back(std::unique_ptr<CompoundType>(value));
        return true;
    }
    return false;
}

} // namespace nbt
