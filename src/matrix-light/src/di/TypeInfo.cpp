#include "di/TypeInfo.h"
#include "common/StringExtensions.h"

#include <regex>

namespace Matrix
{
TypeInfo::TypeInfo(const std::type_info* type)
    : mRawType(type)
    , mFullName(buildTypeName())
{
}

std::type_info const& TypeInfo::getRawType() const
{
    return *mRawType;
}

std::string TypeInfo::getName() const
{
    return mFullName;
}

std::string TypeInfo::buildTypeName()
{
    auto name = mRawType->name();
    auto fullName = Strings::replace(name, "::", ".");
    auto const empty = "";

    fullName = std::regex_replace(fullName, std::regex("(const\\s+|\\s+const)"), empty);
    fullName = std::regex_replace(fullName, std::regex("(volatile\\s+|\\s+volatile)"), empty);
    fullName = std::regex_replace(fullName, std::regex("(static\\s+|\\s+static)"), empty);
    fullName = std::regex_replace(fullName, std::regex("(class\\s+|\\s+class)"), empty);
    fullName = std::regex_replace(fullName, std::regex("(struct\\s+|\\s+struct)"), empty);

    return fullName;
}
} // namespace Matrix
