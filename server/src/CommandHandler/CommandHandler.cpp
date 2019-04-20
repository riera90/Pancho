#include "CommandHandler.hpp"
#include <iostream>

const CommandHandlerResponse CommandHandler::handle(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    std::string module = utils::splitCommand(command);
    
    
    if (module == "/alarm"){
        return AlarmCommandHandler::handle(command);
    }
    
    else if (module == "/speaker"){
        CommandHandlerResponse response;
        response.ack = "not yet implemented";
        return response;
    }
    
    else{
        CommandHandlerResponse response;
        response.ack = "module not found";
        return response;
    }
}
