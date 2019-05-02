#include <pancho/Kernel/Server.hpp>
#include <iostream>

int main()
{
    Server* server = new Server(SERVER_PORT);
    std::string command;
    while (true){
        try {
            command = server->handleNextConnnection();
        }
        catch (...) {
            std::cout<<"error\n";
        }
        std::cout << "command:response <"<< command <<">\n";
    }
    free(server);
    return 0;
}