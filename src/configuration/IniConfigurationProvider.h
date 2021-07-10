#pragma once
#include "IConfiguration.h"
#include "FileConfigurationProvider.h"
#include "../common/StringExtensions.h"

#include "OsINIFile.h"

#include <memory>


namespace Matrix
{

	class IniConfigurationProvider : public FileConfigurationProvider
	{
	public:
		IniConfigurationProvider();

		IniConfigurationProvider(const std::string& filePath);

		~IniConfigurationProvider();

		void load() override;

		bool tryGet(std::string key, std::string& value, std::string defaultValue = "") override;

		bool tryGetValue(const std::string& section, const std::string& key, std::string& value);
				
		template<typename TKey>
		TKey getProperty(const std::string&  section, const std::string& key, TKey defaultValue = TKey())
		{
			std::string value;
			if (tryGetValue(section,key, value))
			{
				if (typeid(TKey) == typeid(std::string)) 
				{
					// special process the quotes, may not necessay?
					value = StringExtensions::replace(value, "\"", "");
				}
				return convertTo<TKey>(value);
			}
			return defaultValue;
		}
		
		template<typename TKey>
		TKey getProperty(const std::string&  fullPath, TKey defaultValue = TKey())
		{
			auto segments = StringExtensions::split(fullPath, ConfigureKeyDelimiter);
			if (segments.size() == 2)
			{
				return getProperty(segments[0], segments[1], defaultValue);
			}

			return defaultValue;
		}

	private:
		std::shared_ptr<OsAbstraction::OsINIFile> mIniFile;
	};
}
