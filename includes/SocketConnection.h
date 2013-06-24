//
//  SocketConnection.h
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#ifndef Web_Server_SocketConnection_h
#define Web_Server_SocketConnection_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

#include "constants.h"
#include "HttpRequestParser.h"
#include "ServerFileSystem.h"
#include "HttpResponseGenerator.h"

class SocketConnection 
{
    private:
    
        int sockfd, newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;
        void error(const char *msg);
        void send_response(std::string urlPath, int fd);
        void write_to_socket(std::string urlPath, int fd);
    
    public:
    
        int get_socket_fd();
        void bind_fd_to_serv_add();
        void listen_for_connections();
        void close_fd();
};

#endif
