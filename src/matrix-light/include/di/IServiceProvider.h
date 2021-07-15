#pragma once
#include "TypeInfo.h"
#include <memory>

namespace Matrix
{
class IServiceProvider
{
public:
    virtual ~IServiceProvider() = default;

    virtual std::shared_ptr<void> getService(const std::shared_ptr<TypeInfo> typeInfo, std::string name = std::string()) = 0;

    template <class TService>
    std::shared_ptr<TService> resolveService(std::string name = std::string())
    {
        auto service = getService(TypeInfo::From<TService>(), name);
        return std::static_pointer_cast<TService>(service);
    }

protected:
    IServiceProvider() = default;
};
} // namespace Matrix
