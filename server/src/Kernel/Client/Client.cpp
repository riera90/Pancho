#include "Client.hpp"

std::string sendMessageToServer(const char* host,
                                int portno,
                                std::string message)
{
    
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    
    if (portno < 0 || strcmp(host, "") == 0) {
        fprintf(stderr,"ERROR invalid hostname or port\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr,"ERROR could not open socket\n");
        exit(2);
    }
    
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR host (server) could not be found\n");
        exit(3);
    }
    
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,
        (char*) &serv_addr.sin_addr.s_addr,
        server->h_length
    );
    
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr,"ERROR connecting\n");
        exit(4);
    }
    
    
    n = write(sockfd, message.c_str(), strlen(message.c_str()));
    if (n < 0) {
        fprintf(stderr,"ERROR writing to the socket\n");
        exit(5);
    }
    
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    
    
    if (n < 0) {
        fprintf(stderr,"ERROR reading from the socket\n");
        exit(6);
    }
    close(sockfd);
    return buffer;
    
}