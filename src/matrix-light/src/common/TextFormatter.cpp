#include "common/TextFormatter.h"
#include "common/ConstStrings.h"

namespace Matrix
{
	TextFormatter & TextFormatter::DefaultTextFormatter()
	{
		static TextFormatter formatter;
		return formatter;
	}

	TextFormatter::TextFormatter(std::string separatorString)
		:mSeparator(separatorString)
	{
	}
}