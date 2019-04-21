#ifndef _PANCHO_ALARM_HANDLER_
#define _PANCHO_ALARM_HANDLER_

#include <string>
#include "Client.hpp"
#include "CommandHandlerResponse.hpp"
#include "commandSplitter.hpp"
#include "shared.hpp"
#include "TrainController.hpp"
#include "WeatherController.hpp"
#include "responses.hpp"

namespace NightStandCommandHandler
{
    const CommandHandlerResponse handle(std::string command);
    
    const CommandHandlerResponse handleButton(std::string command);
    
}

#endif