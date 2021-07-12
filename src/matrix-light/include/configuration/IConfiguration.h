#pragma once
#include <vector>
#include <memory>
#include <map>
#include <any>
#include <sstream>
#include <string>

#include "../common/StringExtensions.h"


namespace Matrix
{
	class IConfigurationSection;

	static const char ConfigureKeyDelimiter = ':';

	template<typename TKey>
	std::string convertToString(const std::string & value)
	{
		return value;
	}

	template<typename TKey>
	TKey convertTo(const std::string & value)
	{
		std::istringstream stream(value);
		TKey target;
				
		if (typeid(TKey) == typeid(std::string))
		{						
			for (size_t i = 0; i < StringExtensions::split(value).size(); i++)
			{
				TKey tempValue;
				stream >> tempValue;
				if (i > 0)
					target += ' ';
				target += tempValue;
			}
		}
		else
		{
			stream >> target;
		}

		return target;
	}

	template<typename TKey>
	std::string toString(TKey value)
	{
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}


	class IConfiguration
	{
	public:

		virtual bool tryGet(std::string key, std::string& value, std::string defaultValue = "") = 0;

		virtual IConfiguration& set(std::string key, std::string value) = 0;

		template<typename TKey>
		IConfiguration& setProperty(std::string name, TKey value)
		{
			auto stringValue = toString<TKey>(value);
			set(name, stringValue);

			return *this;
		}

		template<typename TKey>
		TKey getProperty(std::string key, TKey defaultValue = TKey())
		{
			std::string value;
			if (tryGet(key, value))
			{
				return convertTo<TKey>(value);
			}
			return defaultValue;
		}
	};

}