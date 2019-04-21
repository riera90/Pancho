#ifndef _PANCHO_COMMAND_HANDLER_
#define _PANCHO_COMMAND_HANDLER_

#include "AlarmCommandHandler.hpp"
#include "commandSplitter.hpp"
#include "shared.hpp"

namespace CommandHandler
{   
    const CommandHandlerResponse handle(std::string command);
}

#endif