#include <pancho/Kernel/Server.hpp>

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
        return "ERROR on accept";
    }
    bzero(this->buffer_, BUFFER_LENGTH+1);
    this->n_ = read(this->newsockfd_, this->buffer_, BUFFER_LENGTH);
    if (this->n_ < 0){
        fprintf(stderr,"ERROR readding from the socket\n");
        return "ERROR readding from the socket";
    }
    
    if (strcmp(this->buffer_, "Hello") == 0){
        write(this->newsockfd_, "Hello", 6);
    }else{
        CommandHandlerResponse response;
        response = CommandHandler::handle(this->buffer_);
        this->n_ = write(this->newsockfd_,
                         response.ack.c_str(),
                         response.ack.size());
                         
        for (int i = 0; i < response.packages.size(); i++){
            std::string ack = "";
            ack = sendMessageToServer(inet_ntoa(this->cli_addr_.sin_addr),
                                      NODE_PORT,
                                      response.packages[i].c_str(), 
                                      CONNECTION_RETRIES);
        }
        strcat(this->buffer_, ":");
        strcat(this->buffer_, response.ack.c_str());
        for (int i = 0; i < response.packages.size(); i++){
            strcat(this->buffer_, "|");
            strcat(this->buffer_, response.packages[i].c_str());
        }
    }
    
    if (this->n_ < 0){
        fprintf(stderr,"ERROR writing to the socket\n");
        return "ERROR writing to the socket";
    }
    
    return this->buffer_;
}


Server::~Server ()
{
    close(this->newsockfd_);
    close(this->sockfd_);
}