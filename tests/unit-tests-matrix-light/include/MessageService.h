#pragma once

#include "IMessageService.h"

namespace Matrix
{
class MessageService : public IMessageService
{
public:
    void write(std::string const message) override;
};
} // namespace Matrix
