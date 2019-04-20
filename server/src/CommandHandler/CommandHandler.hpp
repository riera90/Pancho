#ifndef _PANCHO_COMMAND_HANDLER_
#define _PANCHO_COMMAND_HANDLER_

#include "AlarmCommandHandler.hpp"
#include "CommandSplitter.hpp"
#include "shared.hpp"

namespace CommandHandler
{   
    const CommandHandlerResponse handle(std::string command);
}

#endif