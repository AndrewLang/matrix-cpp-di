#pragma once
#include "MapValueDescriptor.h"

#include <memory>
#include <map>
#include <string>
#include <vector>


namespace Matrix
{
	template<class TKey>
	class ObjectMap
	{
	public:
		template<typename TValue>
		ObjectMap& add(TKey key, TValue value)
		{
			auto descriptor = std::make_shared<MapValueDescritor>();
			descriptor->value = std::make_shared<TValue>(value);
			
			internalMap[key] = descriptor;

			return *this;
		}
		
		template<typename TValue>
		TValue getValue(TKey key, TValue defaultValue = TValue())
		{
			auto iterator = internalMap.find(key);
			if (iterator != internalMap.end())
			{
				auto descriptor = iterator->second;
				auto pointer = std::static_pointer_cast<TValue>(descriptor->value);

				return *pointer;
			}
			return defaultValue;
		}

		bool contains(TKey key);

		void clear();

		int size();

		std::vector<TKey> keys();
				
	private:
		std::map<TKey, std::shared_ptr<MapValueDescritor>> internalMap;
	};


	template<class TKey>
	inline bool ObjectMap<TKey>::contains(TKey key)
	{
		auto iterator = internalMap.find(key);
		return iterator != internalMap.end();
	}

	template<class TKey>
	inline void ObjectMap<TKey>::clear()
	{
		internalMap.clear();
	}

	template<class TKey>
	inline int ObjectMap<TKey>::size()
	{
		return static_cast<int>(internalMap.size());
	}

	template<class TKey>
	inline std::vector<TKey> ObjectMap<TKey>::keys()
	{
		std::vector<TKey> keys;

		for (auto &item : internalMap)
		{			
			keys.push_back(item.first);
		}

		return keys;
	}
}