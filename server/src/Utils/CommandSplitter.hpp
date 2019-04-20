#ifndef _PANCHO_COMMAND_SPLITTER_
#define _PANCHO_COMMAND_SPLITTER_

#include <string>

namespace utils
{
    bool isCommand(const std::string &command);
    std::string splitCommand(std::string &command);
}

#endif