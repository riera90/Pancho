#ifndef _PANCHO_ALARM_HANDLER_
#define _PANCHO_ALARM_HANDLER_

#include <string>
#include "Client.hpp"
#include "CommandHandlerResponse.hpp"

namespace AlarmCommandHandler
{
    const CommandHandlerResponse handle(std::string command);
}

#endif