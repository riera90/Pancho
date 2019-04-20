#include "AlarmCommandHandler.hpp"

const CommandHandlerResponse AlarmCommandHandler::handle(std::string command)
{
    CommandHandlerResponse response;
    response.ack = "OK";
    response.package = "hello from\n the other side";
    return response;
}