#ifndef _PANCHO_ALARM_HANDLER_
#define _PANCHO_ALARM_HANDLER_

#include <string>
#include <pancho/Kernel/Client.hpp>
#include <pancho/CommandHandler/CommandHandlerResponse.hpp>
#include <pancho/Utils/commandSplitter.hpp>
#include <pancho/shared.hpp>
#include <pancho/Controller/TrainController.hpp>
#include <pancho/Controller/WeatherController.hpp>
#include <pancho/Utils/responses.hpp>

namespace NightStandCommandHandler
{
    const CommandHandlerResponse handle(std::string command);
    
    const CommandHandlerResponse handleButton(std::string command);
    
}

#endif