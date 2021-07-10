#pragma once

#include <typeinfo>
#include <atomic>
#include <string>

namespace Matrix
{
	class TypeInfo
	{
	public:
		const std::type_info* rawType;
		std::string name;	

		TypeInfo(const std::type_info* type)
			: rawType(type)
			, name(getTypeName())
		{}


		template<class TKey>
		static const std::shared_ptr<TypeInfo> From()
		{
			return std::make_shared<TypeInfo>(&typeid(TKey));
		}

		const TypeInfo* operator=(const std::type_info* type)
		{
			return new TypeInfo(type);
		}

	private:
		static std::atomic<int> InitialCode;

		std::string getTypeName();

	};

}