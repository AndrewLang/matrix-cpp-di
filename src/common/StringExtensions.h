#pragma once


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <locale>
#include <cctype>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <iomanip>
#include <chrono>
#include <limits>
#include <time.h>


namespace Matrix
{
	class StringExtensions
	{
	public:
		//const static int Padding = 25;
		//const static char PaddingChar = ' ';

		static constexpr const int Padding = 25;
		static constexpr const char PaddingChar = ' ';

		static constexpr const char* NewLine = "\n";
		static constexpr const char* Tab = "\t";

		static std::vector<std::string> split(const std::string& value, const char& delimiter = ' ')
		{
			std::vector<std::string> result;

			std::stringstream stream(value);
			std::string segment;
			while (std::getline(stream, segment, delimiter))
			{
				result.push_back(segment);
			}
			return result;
		}

		static std::vector<std::string> split(const std::string& value, const std::vector<std::string> delimiters)
		{
			std::vector<std::string> result;

			std::string remain = value;
			size_t pos = std::string::npos;

			auto findFirstDelimiter = [](const std::string& text, const std::vector<std::string> splitters) {
				auto pos = INT_MAX; 
				std::tuple<int, std::string> posInfo;

				
				for (const auto& spliter : splitters)
				{
					int temp = text.find(spliter);
					if (temp >= 0 && temp < pos)
					{
						pos = temp;
						posInfo = std::make_tuple(pos, spliter);
					}
				}
				return posInfo;
			};

			do
			{
				auto posInfo = findFirstDelimiter(remain, delimiters);
				pos = std::get<0>(posInfo);
				if (pos > 0)
				{
					auto part = remain.substr(0, pos);
					result.push_back(part);

					remain.erase(0, pos + std::get<1>(posInfo).length());
				}
				else 
				{
					result.push_back(remain);
				}

			} while (pos > 0);

			return result;
		}

		static std::string replace(const std::string& original, const std::string& toBeReplace, const std::string& value)
		{
			std::string result = original;
			size_t pos = result.find(toBeReplace);

			while (pos != std::string::npos)
			{
				result.replace(pos, toBeReplace.size(), value);
				pos = result.find(toBeReplace, pos + value.size());
			}
			return result;
		}

		static bool compareIgnoreCase(const std::string& first, const std::string& second)
		{
			if (first.length() == second.length())
			{
				return std::equal(second.begin(), second.end(), first.begin(), compareChar);
			}
			else
			{
				return false;
			}
		}

		static bool compareTrimIgnoreCase(const std::string& first, const std::string& second, const char trimChars[] = " ")
		{
			std::string part1 = trim(first, trimChars);
			std::string part2 = trim(second, trimChars);

			if (part1.length() == part2.length())
			{
				return std::equal(part2.begin(), part2.end(), part1.begin(), compareChar);
			}
			else
			{
				return false;
			}
		}

		static bool isNullOrEmpty(const std::string& value)
		{
			return value.length() <= 0;
		}

		static bool notNullOrEmpty(const std::string& value)
		{
			return value.length() > 0;
		}

		static int indexOf(const std::string& text, const char& value)
		{
			return static_cast<int>(text.find_first_of(value, 0));
		}

		static int indexOf(const std::string& text, const std::string& value)
		{
			return static_cast<int>(text.find(value, 0));
		}

		static bool contains(const std::string& text, const std::string& value, bool ignoreCase = true)
		{
			if (ignoreCase)
			{
				return indexOf(toLower(text), toLower(value)) >= 0;
			}
			else
			{
				return indexOf(text, value) >= 0;
			}
		}

		static std::string textBetween(const std::string& text, const char& start, const char& end)
		{
			int startIndex = indexOf(text, start);
			int endIndex = indexOf(text, end);
			return text.substr(startIndex + 1, endIndex - startIndex - 1);
		}

		static std::string literalString(const std::string& value)
		{
			if (isNullOrEmpty(value))
				return value;

			return replace(value, "\\", R"(\\)");
		}

		static std::string toLower(const std::string& value)
		{
			if (isNullOrEmpty(value))
				return value;

			std::string literal = value;
			std::string result;
			result.resize(literal.size());
			std::transform(literal.begin(), literal.end(), result.begin(), [](unsigned char c) {
				return std::tolower(c);
				});

			return result;
		}

		static std::string toUpper(const std::string& value)
		{
			if (isNullOrEmpty(value))
				return value;

			std::string result;
			result.resize(value.size());
			std::transform(value.begin(), value.end(), result.begin(), [](unsigned char c) {
				return std::toupper(c);
				});

			return result;
		}

		static int parseHex(const std::string& value)
		{
			std::stringstream stream;
			stream << std::hex << value;

			int result;
			stream >> result;
			return result;
		}

		template<typename TKey>
		static TKey convertTo(const std::string & value)
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

		static std::wstring toWString(const std::string& value)
		{
			std::wstringstream stream;
			stream << value.c_str();
			return stream.str();
		}

		static std::string toString(const std::wstring& value)
		{
			std::string result(value.begin(), value.end());
			return result;
		}

		static bool endsWith(const std::string& full, const std::string& end)
		{
			if (full.length() >= end.length()) {
				return (0 == full.compare(full.length() - end.length(), end.length(), end));
			}
			else {
				return false;
			}
		}

		static bool endsWith(const std::string& full, const char& end)
		{
			return endsWith(full, std::string(1, end));
		}

		static bool startsWith(const std::string& full, const std::string& start)
		{
			if (full.length() >= start.length()) {
				return std::equal(start.begin(), start.end(), full.begin());
			}
			else {
				return false;
			}
		}

		static bool startsWith(const std::string& full, const char& start)
		{
			return startsWith(full, std::string(1, start));
		}

		static std::string paddingString(const std::string& value, const char& paddingChar = PaddingChar, const int& padding = Padding)
		{
			std::stringstream stream;
			stream << std::left << std::setfill(paddingChar) << std::setw(padding) << value;

			return stream.str();
		}

		static std::string wrapBySquare(const std::string& value)
		{
			return "[" + value + "]";
		}

		static std::string getTimestamp()
		{
			std::time_t rawtime = std::time(0);
			static char result[20];
			

#if defined (__linux__)	
			struct tm* timeinfo = std::localtime(&rawtime);
			strftime(result, sizeof(result), "%Y-%m-%d %H:%M:%S", timeinfo);
#elif defined(_WIN32)			
			struct tm timeinfo;
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			strftime(result, sizeof(result), "%Y-%m-%d %H:%M:%S", &timeinfo);
#endif
					
			

			return result;
		}

		static std::string trimStart(const std::string& value, const char trimChars[] = " ")
		{
			auto result = value;
			result.erase(0, result.find_first_not_of(trimChars));
			return result;
		}

		static std::string trimEnd(const std::string& value, const char trimChars[] = " ")
		{
			auto result = value;
			result.erase(result.find_last_not_of(trimChars) + 1);
			return result;
		}

		static std::string trim(const std::string& value, const char trimChars[] = " ")
		{
			auto result = trimStart(value, trimChars);
			return trimEnd(result, trimChars);
		}

		static std::string toHex(const int value)
		{
			std::stringstream stream;
			stream << std::hex << value;

			return stream.str();
		}

		static std::string toString(const std::vector<char> chars)
		{
			std::stringstream stream;

			for (auto& c : chars)
			{
				if (c == '\0')
					continue;
				stream << c;
			}

			return stream.str();
		}

	private:
		static bool compareChar(unsigned char first, unsigned char second)
		{
			return std::tolower(first) == std::tolower(second);
		}
	};

	using Strings = StringExtensions;
}