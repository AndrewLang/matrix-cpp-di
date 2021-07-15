#pragma once
#include "TypeInfo.h"

#include <map>

namespace Matrix
{
template <class TKey>
class TypeMap
{
public:
    void add(const std::shared_ptr<TypeInfo> type, TKey value);
    TKey get(const std::shared_ptr<TypeInfo> type);
    bool contains(const std::shared_ptr<TypeInfo> type);
    void clear();
    int size();

private:
    std::map<const std::string, TKey> internalMap;
};

template <class TKey>
inline void TypeMap<TKey>::add(const std::shared_ptr<TypeInfo> type, TKey value)
{
    internalMap.insert(std::make_pair(type->getName(), value));
}

template <class TKey>
inline TKey TypeMap<TKey>::get(const std::shared_ptr<TypeInfo> type)
{
    auto iterator = internalMap.find(type->getName());
    if (iterator != internalMap.end())
    {
        return iterator->second;
    }
    return NULL;
}

template <class TKey>
inline bool TypeMap<TKey>::contains(const std::shared_ptr<TypeInfo> type)
{
    auto iterator = internalMap.find(type->getName());
    return iterator != internalMap.end();
}

template <class TKey>
inline void TypeMap<TKey>::clear()
{
    internalMap.clear();
}

template <class TKey>
inline int TypeMap<TKey>::size()
{
    return static_cast<int>(internalMap.size());
}

} // namespace Matrix
