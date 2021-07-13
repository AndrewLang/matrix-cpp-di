#pragma once
#include <string>
#include <sstream>


namespace Matrix
{
	class TextFormatter
	{
	public:
		static TextFormatter& DefaultTextFormatter();

		TextFormatter(std::string separatorString = " ");
		

		template< typename TKey >
		std::string format(const TKey& text)
		{
			std::stringstream stream;
			stream << text << mSeparator;
			return stream.str();
		}

		template< typename TKey, typename ... Args >
		std::string format(const TKey& first, Args ... args)
		{
			return format(first) + format(args...);
		}
		

	private :
		std::string mSeparator;
	};
}