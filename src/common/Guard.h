#pragma once
#include "ArgumentNullException.h"

namespace Matrix
{
	class Guard
	{
	public:
		template<typename TKey>
		static void notNull(TKey arg, const std::string& name);

		static void notEmpty(const std::string& value, const std::string& name);
	};

	template<typename TKey>
	inline void Guard::notNull(TKey arg, const std::string& name)
	{		
		//if (std::is_null_pointer<decltype(arg)>::value)
		if(arg == NULL)
			throw ArgumentNullException(name);
	}
}
