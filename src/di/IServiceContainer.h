#pragma once
#include "TypeInfo.h"
#include "IServiceProvider.h"
#include "ServiceDescriptor.h"

namespace Matrix
{
	class IServiceContainer : public IServiceProvider
	{
	public:
		virtual ~IServiceContainer() { }

		virtual IServiceContainer & registerService(std::shared_ptr<ServiceDescriptor> descriptor) = 0;

		
		template<class TService>
		IServiceContainer & transient()
		{
			auto descriptor = ServiceDescriptor::Transient<TService>();

			return registerService(descriptor);
		}

		template<class TService>
		IServiceContainer & transient(GenericObjectFactory<TService> factory, const std::string name = std::string())
		{
			auto descriptor = ServiceDescriptor::Transient<TService, TService>(factory, name);

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & transient()
		{
			auto descriptor = ServiceDescriptor::Transient<TService, TImplementation>();

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & transient(GenericObjectFactory<TService> factory, const std::string name = std::string())
		{
			auto descriptor = ServiceDescriptor::Transient<TService, TImplementation>(factory, name);

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & transient(ParameterFactoryCreator<TService> factoryResolver, const std::string name = std::string())
		{
			InstanceCreatorContext context(dynamic_cast<IServiceProvider*>(this), factoryResolver);

			auto descriptor = ServiceDescriptor::Transient<TService, TImplementation>(std::make_shared<InstanceCreatorContext>(context), name);

			return registerService(descriptor);
		}

		
		template<class TService>
		IServiceContainer & singleton()
		{
			auto descriptor = ServiceDescriptor::Singleton<TService>();

			return registerService(descriptor);
		}

		template<class TService>
		IServiceContainer & singleton(GenericObjectFactory<TService> factory, const std::string name = std::string())
		{
			auto descriptor = ServiceDescriptor::Singleton<TService, TService>(factory, name);

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & singleton(const std::string name = std::string())
		{
			auto descriptor = ServiceDescriptor::Singleton<TService, TImplementation>(name);
			

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & singleton(GenericObjectFactory<TService> factory, const std::string name = std::string())
		{
			auto descriptor = ServiceDescriptor::Singleton<TService, TImplementation>(factory, name);

			return registerService(descriptor);
		}

		template<class TService, class TImplementation>
		IServiceContainer & singleton(ParameterFactoryCreator<TService> factoryResolver, const std::string name = std::string())
		{
			InstanceCreatorContext context(dynamic_cast<IServiceProvider*>(this), factoryResolver);

			auto descriptor = ServiceDescriptor::Singleton<TService, TImplementation>(std::make_shared<InstanceCreatorContext>(context), name);

			return registerService(descriptor);
		}



		template<class TService>
		IServiceContainer & instance(std::shared_ptr<TService> instance)
		{
			auto descriptor = ServiceDescriptor::Instance<TService>(instance);

			registerService(descriptor);

			return *this;
		}

	};
}