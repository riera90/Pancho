#include <pancho/CommandHandler/NightStandCommandHandler.hpp>


const CommandHandlerResponse NightStandCommandHandler::handle(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    std::string action = utils::splitCommand(command);
    
    if (action == "/button"){
        return handleButton(command);
    }
    
    else {
        CommandHandlerResponse response;
        response.ack = "action not found";
        return response;
    }   
    
}




const CommandHandlerResponse NightStandCommandHandler::handleButton(std::string command)
{
    if (!utils::isCommand(command)){
        CommandHandlerResponse response;
        response.ack = "NOT A COMMAND";
        return response;
    }
    
    CommandHandlerResponse response;
    response.ack = ACK_OK;
    std::string client_response;
    
    if (command == "/press"){
        client_response = sendMessageToServer(SPEAKER,
                                              NODE_PORT,
                                              "/music/stop",
                                              CONNECTION_RETRIES);
        if (!utils::responseOk(client_response)){
            response.ack = client_response;
            response.packages.emplace_back("there is an\nerror somewhere");
        }
        response.packages.emplace_back("tren a las xx:xx\nsal a las xx:xx");
        response.packages.emplace_back(WeatherController::getReport());
        return response;
    }
    
    else if (command == "/hold"){
        client_response = sendMessageToServer(SPEAKER ,
                                              NODE_PORT,
                                              "/music/stop",
                                              CONNECTION_RETRIES);
        if (!utils::responseOk(client_response)){
            response.ack = client_response;
            response.packages.push_back("there is an\nerror somewhere");
        }
        response.packages.push_back("alarm stopped");
        response.packages.push_back("tren a las xx:xx\nsal a las xx:xx");
        response.packages.push_back(WeatherController::getReport());
        return response;
    }
    
    else {
        response.ack = "action not found";
        return response;
    }   
    
}