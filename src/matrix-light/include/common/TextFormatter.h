#pragma once
#include <string>
#include <sstream>


namespace Matrix
{
	const static std::string SPACE = " ";
	const static std::string Empty = "";

	class TextFormatter
	{
	public:
		static TextFormatter& DefaultTextFormatter();

		TextFormatter(std::string separatorString = SPACE);
		
		std::string separator = SPACE;

		template< typename TKey >
		std::string format(const TKey& text)
		{
			std::stringstream stream;
			stream << text << separator;
			return stream.str();
		}

		template< typename TKey, typename ... Args >
		std::string format(const TKey& first, Args ... args)
		{
			return format(first) + format(args...);
		}
		
	};
}