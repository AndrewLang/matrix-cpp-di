#pragma once

#include "IServiceContainer.h"
#include "InstanceDescriptor.h"
#include "ServiceLifetime.h"
#include "TypeMap.h"
#include "common/StringExtensions.h"

#include <stdexcept>

namespace Matrix
{
class ServiceContainer : public IServiceContainer
{
public:
    ServiceContainer();

    ServiceContainer(ServiceContainer&& container);

    ~ServiceContainer();

    IServiceContainer& registerService(std::shared_ptr<ServiceDescriptor> descriptor) override;

    std::shared_ptr<void> getService(const std::shared_ptr<TypeInfo> typeInfo, const std::string name = std::string()) override;

protected:
private:
    std::vector<std::shared_ptr<ServiceDescriptor>> mDescriptors;

    std::vector<std::shared_ptr<InstanceDescriptor>> mInstances;

    std::shared_ptr<ServiceDescriptor> findDescriptor(std::string typeName, std::string instanceName = std::string());

    std::shared_ptr<InstanceDescriptor> findInstance(const std::shared_ptr<TypeInfo> type, std::string instanceName = std::string());

    template <class TKey>
    std::shared_ptr<TKey> resolveInstance(const std::shared_ptr<TypeInfo> type, const std::string name = std::string())
    {
        auto descriptor = findDescriptor(type->getName(), name);
        if (descriptor)
        {
            switch (descriptor->lifetime)
            {
            case ServiceLifetime::Scoped:
                return nullptr;
            case ServiceLifetime::Transient: {
                auto instance = descriptor->getInstance<TKey>();
                return std::static_pointer_cast<TKey>(instance);
            }
            case ServiceLifetime::Singleton:
            default: {
                auto instance = findInstance(type, name);
                if (nullptr != instance)
                {
                    return std::static_pointer_cast<TKey>(instance->instance);
                }
                else
                {
                    auto instance = descriptor->getInstance<TKey>();

                    auto instanceDescriptor = std::make_shared<InstanceDescriptor>(type, instance, name);
                    mInstances.push_back(instanceDescriptor);

                    return std::static_pointer_cast<TKey>(instance);
                }
            }
            }
        }
        else
        {
            throw new std::runtime_error("No type registration found for " + type->getName());
        }
        return nullptr;
    }
};
} // namespace Matrix
