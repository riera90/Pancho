#include "Server.hpp"


Server::Server (int portno = -1)
{
    if (portno < 0) {
        fprintf(stderr,"ERROR, no valid port provided\n");
        exit(1);
    }
    this->portno_ = portno;
    
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0) {
        fprintf(stderr,"ERROR, could not open socket\n");
        exit(2);
    }
    
    bzero((char*) &this->serv_addr_, sizeof(this->serv_addr_));
    this->serv_addr_.sin_family = AF_INET;
    this->serv_addr_.sin_addr.s_addr = INADDR_ANY;
    this->serv_addr_.sin_port = htons(this->portno_);
    if (bind(this->sockfd_, (struct sockaddr *) &this->serv_addr_,
            sizeof(this->serv_addr_)) < 0) {
        fprintf(stderr,"ERROR on binding\n");
        exit(3);
    }
    listen(this->sockfd_, 5);
    this->clilen_ = sizeof(this->cli_addr_);
}


std::string Server::handleNextConnnection()
{
    this->newsockfd_ = accept(this->sockfd_,
                            (struct sockaddr *) &this->cli_addr_,
                            &this->clilen_
                        );
    if (this->newsockfd_ < 0 ){
        fprintf(stderr,"ERROR on accept\n");
        exit(4);
    }
    bzero(this->buffer_, 256);
    this->n_ = read(this->newsockfd_, this->buffer_, 255);
    if (this->n_ < 0){
        fprintf(stderr,"ERROR readding from the socket\n");
        exit(6);
    }
    CommandHandlerResponse response;
    response = CommandHandler::handle(this->buffer_);
    this->n_ = write(this->newsockfd_, response.ack.c_str(), 18);
    if (strcmp(response.package.c_str(), "") != 0){
        sendMessageToServer(inet_ntoa(this->cli_addr_.sin_addr), 1, response.package.c_str());
    }
    
    if (this->n_ < 0){
        fprintf(stderr,"ERROR writing to the socket\n");
        exit(7);
    }
    strcat(this->buffer_, ":");
    strcat(this->buffer_, response.ack.c_str());
    strcat(this->buffer_, "->");
    strcat(this->buffer_, response.package.c_str());
    return this->buffer_;
}


Server::~Server ()
{
    close(this->newsockfd_);
    close(this->sockfd_);
}