#include "Server.hpp"

int main()
{
    Server* server = new Server(8000);
    std::string command;
    while (true){
        command = server->getNextConnnection();
        std::cout << "command: <"<< command <<">\n";
    }
    free(server);
    return 0;
}