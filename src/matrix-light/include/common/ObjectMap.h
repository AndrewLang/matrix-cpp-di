#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <any>

namespace Matrix
{
	template<class TKey>
	class ObjectMap
	{
	public:
		template<typename TValue>
		ObjectMap& add(TKey key, TValue value)
		{			
			mInternalMap[key] = value;

			return *this;
		}
		
		template<typename TValue>
		TValue getValue(TKey key, TValue defaultValue = TValue())
		{
			auto iterator = mInternalMap.find(key);
			if (iterator != mInternalMap.end())
			{
				return std::any_cast<TValue>(iterator->second);
			}
			return defaultValue;
		}

		bool contains(TKey key);

		void clear();

		int size();

		std::vector<TKey> keys();
				
	private:		
		std::map<TKey, std::any> mInternalMap;
	};


	template<class TKey>
	inline bool ObjectMap<TKey>::contains(TKey key)
	{
		auto iterator = mInternalMap.find(key);
		return iterator != mInternalMap.end();
	}

	template<class TKey>
	inline void ObjectMap<TKey>::clear()
	{
		mInternalMap.clear();
	}

	template<class TKey>
	inline int ObjectMap<TKey>::size()
	{
		return static_cast<int>(mInternalMap.size());
	}

	template<class TKey>
	inline std::vector<TKey> ObjectMap<TKey>::keys()
	{
		std::vector<TKey> keys;

		for (auto &item : mInternalMap)
		{			
			keys.push_back(item.first);
		}

		return keys;
	}
}