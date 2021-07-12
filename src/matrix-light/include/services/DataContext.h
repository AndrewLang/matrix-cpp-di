#pragma once
#include "common/ObjectMap.h"
#include "di/IServiceProvider.h"

#include <map>
#include <string>
#include <any>


namespace Matrix
{
	class DataContext
	{
	public:
		DataContext();

		DataContext(std::shared_ptr<IServiceProvider> serviceProvider);

		~DataContext();

		std::shared_ptr<IServiceProvider> services();

		template<typename TKey>
		TKey getProperty(std::string key, TKey defaultValue = TKey())
		{
			if (mDataContainer.contains(key))
			{
				return mDataContainer.getValue<TKey>(key);
			}
			else
			{
				setProperty(key, defaultValue);
			}

			return defaultValue;
		}

		template<typename TKey>
		DataContext& setProperty(std::string name, TKey value)
		{
			mDataContainer.add<TKey>(name, value);
			return *this;
		}

		DataContext& clear();

	private :
		ObjectMap<std::string> mDataContainer;
		std::shared_ptr<IServiceProvider> mServiceProvider;

	protected:
		void copy(DataContext& context);
	};

}