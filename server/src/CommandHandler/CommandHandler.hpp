#ifndef _PANCHO_COMMAND_HANDLER_
#define _PANCHO_COMMAND_HANDLER_

#include "CommandHandlerResponse.hpp"
#include "NightStandCommandHandler.hpp"
#include "SpeakerCommandHandler.hpp"
#include "commandSplitter.hpp"
#include "shared.hpp"

namespace CommandHandler
{   
    const CommandHandlerResponse handle(std::string command);
}

#endif