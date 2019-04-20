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
    
    if (command == "/button/press"){
        sendMessageToServer(SPEAKERS, NODE_PORT, "/music/stop");
        response.packages.push_back("tren a las xx:xx\nsal a las xx:xx");
        response.packages.push_back("Meteorologia:\ncalor");
        return response;
    }
    
    else if (command == "/button/hold"){
        sendMessageToServer(SPEAKERS, NODE_PORT, "/music/stop");
        response.packages.push_back("alarm stopped");
        return response;
    }
    
    else {
        response.ack = "action not found";
        return response;
    }   
    
}