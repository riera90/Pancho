#ifndef _PANCHO_KERNEL_SERVER_
#define _PANCHO_KERNEL_SERVER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>


class Server
{
    private:
        int sockfd_, newsockfd_, portno_, n_;
        socklen_t clilen_;
        char buffer_[256];
        struct sockaddr_in serv_addr_, cli_addr_;

    public:
        Server (int portno);
        std::string getNextConnnection();
        ~Server ();
};

#endif
