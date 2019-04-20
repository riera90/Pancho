#include "AlarmCommandHandler.hpp"
#include <iostream>

const CommandHandlerResponse AlarmCommandHandler::handle(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    std::string module_name = utils::splitCommand(command);
    
    CommandHandlerResponse response;
    response.ack = ACK_OK;
    response.packages.push_back(command);
    
    if (command == "/button/press"){
        response.packages.push_back("alarm snoozed");
        return response;
    }
    
    else if (command == "/button/hold"){
        response.packages.push_back("alarm stopped");
        return response;
    }
    
    else {
        response.ack = "action not found";
        return response;
    }   
    
}