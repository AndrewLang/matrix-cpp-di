
#pragma once
#include "VectorExtensions.h"
#include <map>

namespace Matrix
{
	class MapExtensions 
	{
	public:
		template<typename TKey, typename TValue>
		static TValue get(std::map<TKey, TValue> map, TKey key, TValue defaultValue = TValue())
		{
			auto iterator = map.find(key);
			if (iterator != map.end())
			{
				return iterator->second;
			}
			return defaultValue;
		}
	};

	using Maps = MapExtensions;
}