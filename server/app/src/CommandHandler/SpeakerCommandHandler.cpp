#include <pancho/CommandHandler/SpeakerCommandHandler.hpp>


const CommandHandlerResponse SpeakerCommandHandler::handle(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    std::string action = utils::splitCommand(command);
    
    if (action == "/music"){
        return handleMusic(command);
    }
    
    else {
        CommandHandlerResponse response;
        response.ack = "action not found";
        return response;
    }   
    
}


const CommandHandlerResponse SpeakerCommandHandler::handleMusic(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    CommandHandlerResponse response;
    std::string client_response;
    
    if (command == "/play"){
        response.ack = sendMessageToServer(SPEAKER,
                                           NODE_PORT,
                                           "/music/play",
                                           CONNECTION_RETRIES);
        return response;
    }
    
    else if (command == "/stop"){
        response.ack = sendMessageToServer("localhost",
                                           NODE_PORT,
                                           "/music/stop",
                                           CONNECTION_RETRIES);
        return response;
    }
    
    else {
        response.ack = "ERROR, action not found";
        return response;
    }   
}
