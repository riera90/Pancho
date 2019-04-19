#ifndef _PANCHO_KERNEL_CLIENT_
#define _PANCHO_KERNEL_CLIENT_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>


std::string sendMessageToServer(const char* host,
                                int portno,
                                std::string message);


#endif
