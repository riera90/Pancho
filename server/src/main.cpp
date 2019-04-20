#include "Server.hpp"
#include "CommandHandler.hpp"
#include <iostream>

int main()
{
    Server* server = new Server(SERVER_PORT);
    std::string command;
    while (true){
        command = server->handleNextConnnection();
        std::cout << "command:response <"<< command <<">\n";
    }
    free(server);
    return 0;
}