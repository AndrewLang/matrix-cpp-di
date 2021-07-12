#include "configuration/IConfiguration.h"
#include "configuration/IniConfigurationProvider.h"
#include "io/File.h"
#include "common/FileNotExistsException.h"


namespace Matrix
{
	using std::string;
	//using OsAbstraction::OsINIFile;

	IniConfigurationProvider::IniConfigurationProvider()
	{
	}

	IniConfigurationProvider::IniConfigurationProvider(const string & filePath)
	{
		fullPath = filePath;
	}

	IniConfigurationProvider::~IniConfigurationProvider()
	{
	}

	void IniConfigurationProvider::load()
	{
		if (!File::exists(fullPath))
			throw FileNotExistsException(fullPath);


		//mIniFile = std::make_shared<OsINIFile>(fullPath);
	}

	bool IniConfigurationProvider::tryGet(string key, string & value, string defaultValue)
	{
		auto segments = StringExtensions::split(fullPath, ConfigureKeyDelimiter);
		if (segments.size() == 2)
		{
			return tryGet(segments[0], segments[1], value);
		}
		
		return false;
	}

	bool IniConfigurationProvider::tryGetValue(const string & section, const string & key, string & value)
	{
		string temp;
		/*bool success = mIniFile->getValue(section, key, temp);

		value = StringExtensions::replace(temp, "\"", "");*/

		return true;
	}
}
