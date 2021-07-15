#pragma once

#include <string>

namespace Matrix
{
class IMessageService
{
public:
    virtual ~IMessageService() = default;

    virtual void write(std::string const message) = 0;

protected:
    IMessageService() = default;
};
} // namespace Matrix
