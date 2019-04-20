#include "CommandHandler.hpp"

const CommandHandlerResponse CommandHandler::handle(std::string command)
{
    command = command.substr(1, command.length());
    std::string module = command.substr(0, command.find('/'));
    command = command.substr(command.find('/'), command.length());
    
    CommandHandlerResponse response;
    
    if (module == "alarm"){
        return AlarmCommandHandler::handle(command);
    }
    else if (module == "speaker"){
        response.ack = "not yet implemented";
        return response;
    }
    else{
        response.ack = "module not found";
        return response;
    }
}
