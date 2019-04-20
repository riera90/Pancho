#ifndef _PANCHO_COMMAND_HANDLER_RESPONSE_
#define _PANCHO_COMMAND_HANDLER_RESPONSE_

#include <string>
#include <vector>

struct CommandHandlerResponse
{
    std::string ack = "";
    std::vector <std::string> packages;
};

#endif
