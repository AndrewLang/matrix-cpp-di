#pragma once

#include <atomic>
#include <string>
#include <typeinfo>

namespace Matrix
{
class TypeInfo
{
public:
    explicit TypeInfo(const std::type_info* type);

    std::type_info const& getRawType() const;

    std::string getName() const;

    template <class TKey>
    static const std::shared_ptr<TypeInfo> From()
    {
        return std::make_shared<TypeInfo>(&typeid(TKey));
    }

    const TypeInfo* operator=(const std::type_info* type)
    {
        return new TypeInfo(type);
    }

    bool operator==(TypeInfo const& info) const
    {
        return getRawType() == info.getRawType();
    }

private:
    const std::type_info* mRawType;
    std::string mFullName;

    static std::atomic<int> InitialCode;

    std::string buildTypeName();
};

} // namespace Matrix
