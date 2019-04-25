#ifndef _PANCHO_COMMAND_HANDLER_
#define _PANCHO_COMMAND_HANDLER_

#include <pancho/CommandHandler/CommandHandlerResponse.hpp>
#include <pancho/CommandHandler/NightStandCommandHandler.hpp>
#include <pancho/CommandHandler/SpeakerCommandHandler.hpp>
#include <pancho/Utils/commandSplitter.hpp>
#include <pancho/shared.hpp>

namespace CommandHandler
{   
    const CommandHandlerResponse handle(std::string command);
}

#endif