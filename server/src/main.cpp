#include "Server.hpp"
#include "CommandHandler.hpp"
#include <iostream>

int main()
{
    Server* server = new Server(8000);
    std::string command;
    while (true){
        command = server->handleNextConnnection();
        std::cout << "command:response <"<< command <<">\n";
    }
    free(server);
    return 0;
}