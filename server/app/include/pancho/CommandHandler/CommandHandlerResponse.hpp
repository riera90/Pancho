#ifndef _PANCHO_COMMAND_HANDLER_RESPONSE_
#define _PANCHO_COMMAND_HANDLER_RESPONSE_

#include <string>
#include <vector>
#include <pancho/shared.hpp>

struct CommandHandlerResponse
{
    std::string ack = ACK_OK;
    std::vector <std::string> packages;
};

#endif
