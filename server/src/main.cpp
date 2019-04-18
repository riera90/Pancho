#include "Server.hpp"

int main()
{
    Server* server = new Server(8000);
    std::string retval;
    while (true){
        retval = server->getNextConnnection();
        std::cout << "retval: " << retval << '\n';
    }
    free(server);
    return 0;
}