#include <pancho/Utils/commandSplitter.hpp>


bool utils::isCommand(const std::string &command)
{
    if (command.find('/') != 0){
        return false;
    }
    return true;
}


std::string utils::splitCommand(std::string &command)
{
    /* TODO make this so it dosen't crash the hole system when an invalid command is given
     *  an error occurs in the command /nightstand/button
     */

    if (!isCommand(command))
        return "ERROR, not a command";

    if (command.size() < 2)
        return "ERROR, missing command";

    std::string actual_command;

    if (command.find('/', 1)) {
        actual_command = command.substr(0, command.find('/', 1));
        command = command.substr(command.find('/', 1), command.length());
    }
    else {
        actual_command = command.substr(0, command.size());
        command = "";
    }

    return actual_command;
}

