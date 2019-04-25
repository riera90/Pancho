#ifndef _PANCHO_SPEAKER_COMMAND_HANDLER_
#define _PANCHO_SPEAKER_COMMAND_HANDLER_

#include <string>
#include <pancho/Utils/commandSplitter.hpp>
#include <pancho/Utils/responses.hpp>
#include <pancho/CommandHandler/CommandHandlerResponse.hpp>
#include <pancho/shared.hpp>
#include <pancho/Kernel/Client.hpp>

namespace SpeakerCommandHandler
{
    const CommandHandlerResponse handle(std::string command);
    const CommandHandlerResponse handleMusic(std::string command);
}

#endif