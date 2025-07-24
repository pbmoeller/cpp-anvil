#include "cpp-anvil/nbt/list_tag.hpp"

#include <algorithm>

namespace anvil {

bool ListTag::push_back(std::unique_ptr<BasicTag> value)
{
    if(value) {
        if(empty()) {
            m_listType = value->type();
        }
        if(value->type() == m_listType) {
            m_value.push_back(std::move(value));
            return true;
        }
    }
    return false;
}

bool ListTag::push_back(BasicTag* value)
{
    if(value) {
        if(empty()) {
            m_listType = value->type();
        }
        if(value->type() == m_listType) {
            m_value.push_back(std::unique_ptr<BasicTag>(value));
            return true;
        }
    }
    return false;
}

bool ListTag::push_back(const BasicTag& value)
{
    if(empty()) {
        m_listType = value.type();
    }
    if(value.type() == m_listType) {
        m_value.push_back(value.clone());
        return true;
    }
    return false;
}

std::unique_ptr<BasicTag> ListTag::takeAt(size_type index)
{
    std::unique_ptr<BasicTag> val = std::move(m_value[index]);
    eraseAt(index);
    return val;
}

std::unique_ptr<BasicTag> ListTag::take(BasicTag* tag)
{
    std::unique_ptr<BasicTag> val;
    auto it =
        std::find_if(m_value.begin(), m_value.end(),
                     [tag](const std::unique_ptr<BasicTag>& ptr) { return ptr.get() == tag; });
    if(it != m_value.end()) {
        val = std::move(*it);
        m_value.erase(it);
    }
    return val;
}

bool ListTag::erase(BasicTag* tag)
{
    auto it =
        std::find_if(m_value.begin(), m_value.end(),
                     [tag](const std::unique_ptr<BasicTag>& ptr) { return ptr.get() == tag; });
    if(it != m_value.end()) {
        m_value.erase(it);
        return true;
    }
    return false;
}

} // namespace anvil
