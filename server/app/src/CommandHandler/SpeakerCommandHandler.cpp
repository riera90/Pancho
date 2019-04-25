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
    response.ack = ACK_OK;
    std::string client_response = "";
    
    if (command == "/music/play"){
        client_response = sendMessageToServer(SPEAKER,
                                              NODE_PORT,
                                              "/music/play",
                                              CONNECTION_RETRIES);
        if (!utils::responseOk(client_response)){
            response.ack = client_response;
        }
        return response;
    }
    
    else if (command == ""){
        client_response = sendMessageToServer(SPEAKER,
                                              NODE_PORT,
                                              "/music/stop",
                                              CONNECTION_RETRIES);
        if (!utils::responseOk(client_response)){
            response.ack = client_response;
        }
        return response;
    }
    
    else {
        response.ack = "action not found";
        return response;
    }   
}
