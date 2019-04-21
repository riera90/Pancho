#ifndef _PANCHO_COMMAND_HANDLER_
#define _PANCHO_COMMAND_HANDLER_

#include "commandSplitter.hpp"
#include "responses.hpp"
#include "CommandHandlerResponse.hpp"
#include "shared.hpp"
#include "Client.hpp"

namespace SpeakerCommandHandler
{
    const CommandHandlerResponse handle(std::string command);
    const CommandHandlerResponse handleMusic(std::string command);
}

#endif