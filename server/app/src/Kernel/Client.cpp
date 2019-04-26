#include <pancho/Kernel/Client.hpp>

std::string sendMessageToServer(const char* host,
                                int portno,
                                std::string message,
                                int retries)
{
    std::string response = "";
    int i = 0;
    do {
        response = sendMessageToServer(host, portno, message);
        i++;
    } while(response != ACK_OK && i < retries);
    return response;
}


std::string sendMessageToServer(const char* host,
                                int portno,
                                std::string message)
{
    
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_LENGTH+1];
    
    if (portno < 0 || strcmp(host, "") == 0) {
        fprintf(stderr,"ERROR invalid hostname or port\n");
        return "ERROR, invalid hostname or port";
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr,"ERROR could not open socket\n");
        return "ERROR, could not open socket";
    }
    
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR host could not be found\n");
        return "ERROR, host could not be found";
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
        return "ERROR, could not connect";
    }
    
    
    n = write(sockfd, message.c_str(), strlen(message.c_str()));
    if (n < 0) {
        fprintf(stderr,"ERROR writing to the socket\n");
        return "ERROR, writing to the socket";
    }
    
    bzero(buffer,BUFFER_LENGTH+1);
    n = read(sockfd, buffer, BUFFER_LENGTH);
    
    
    if (n < 0) {
        fprintf(stderr,"ERROR reading from the socket\n");
        return "ERROR, reading from the socket";
    }
    close(sockfd);
    return buffer;
}