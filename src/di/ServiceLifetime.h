#pragma once
#include <vector>
#include <typeinfo>
#include <functional>
#include <memory>

namespace Matrix
{
	class IServiceProvider;

	enum class ServiceLifetime
	{
		Singleton,
		Scoped,
		Transient
	};



	template<typename TKey, typename  ... TArgs>
	std::unique_ptr<TKey> uniqueInstanceFactory(TArgs&&... args)
	{
		return std::make_unique<TKey>(args...);
	};

	template<typename TKey, typename  ... TArgs>
	std::shared_ptr<TKey> sharedInstanceFactory(TArgs&&... args)
	{
		return std::make_shared<TKey>(args...);
	};


	using ObjectFactory = std::function<std::shared_ptr<void>()>;

	using ObjectFactoryCreator = std::function<ObjectFactory()>;
	   
	template<class TService>
	ObjectFactory DefaultInstanceFactory() {
		return [=]() {		
			return std::make_shared<TService>();
		};
	};


	template<typename TKey>
	using GenericObjectFactory = std::function<std::shared_ptr<TKey>()>;

	template<typename TKey, typename  ... TArgs>
	GenericObjectFactory<TKey> ParameterInstanceFactory(TArgs&&... args)
	{
		return [=]() {
			return std::make_shared<TKey>(args...);
		};
	};

	template<typename TKey, typename ... TArgs>
	using ParameterFactoryCreator = std::function<GenericObjectFactory<TKey>(IServiceProvider* serviceProvider) >;
	
}