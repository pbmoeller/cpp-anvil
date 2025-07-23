#include "cpp-anvil/nbt/compound_tag.hpp"

#include <algorithm>

namespace anvil {

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

bool CompoundTag::push_back(std::unique_ptr<BasicTag> value) {
    if(value) {
        m_value.push_back(std::move(value));
        return true;
    }
    return false;
}

bool CompoundTag::push_back(BasicTag *value) {
    if(value) {
        m_value.push_back(std::unique_ptr<BasicTag>(value));
        return true;
    }
    return false;
}

bool CompoundTag::push_back(const BasicTag &value)
{
    m_value.push_back(value.clone());
    return true;
}

std::unique_ptr<BasicTag> CompoundTag::takeAt(size_type index)
{
    std::unique_ptr<BasicTag> val = std::move(m_value[index]);
    eraseAt(index);
    return val;
}

std::unique_ptr<BasicTag> CompoundTag::take(BasicTag *tag)
{
    std::unique_ptr<BasicTag> val;
    iterator it = std::find_if(m_value.begin(), m_value.end(),
                               [tag](const std::unique_ptr<BasicTag> &ptr) { return ptr.get() == tag; });
    if(it != m_value.end()) {
        val = std::move(*it);
        m_value.erase(it);
    }
    return val;
}

bool CompoundTag::erase(BasicTag *tag)
{
    iterator it = std::find_if(m_value.begin(), m_value.end(),
                               [tag](const std::unique_ptr<BasicTag> &ptr) { return ptr.get() == tag; });
    if(it != m_value.end()) {
        m_value.erase(it);
        return true;
    }
    return false;
}

} // namespace anvil
