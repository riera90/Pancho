#include "CommandSplitter.hpp"

namespace utils
{

    bool isCommand(const std::string &command)
    {
        if (command.find('/') != 0){
            return false;
        }
        return true;
    }


    std::string splitCommand(std::string &command)
    {
        if (!isCommand(command))
            return "ERROR, not a command";
            
        std::string actual_command = command.substr(0, command.find('/', 1));
        command = command.substr(command.find('/', 1), command.length());
        
        return actual_command;
    }

}