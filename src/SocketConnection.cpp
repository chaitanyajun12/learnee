//
//  SocketConnection.cpp
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#include <iostream>
#include "SocketConnection.h"

int SocketConnection::get_socket_fd()
{
    int optval = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    } else {
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    }

    return sockfd;
}

void SocketConnection::bind_fd_to_serv_add()
{
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT_NO);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
}

void SocketConnection::listen_for_connections()
{
    int pid, n;
    listen(sockfd, QUEUED_REQUESTS);

    while(1)
    {
        clilen = sizeof(cli_addr);

        std::cout << "Before accepting a connection\n";
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accepting connection");
        
        pid = fork();

        if(pid < 0)
            error("ERROR on fork()");
        
        if(pid == 0) {  
            
            close(sockfd);
            char buffer[1024];
            bzero(buffer, 1024);
            
            n = recv(newsockfd, buffer, 1024, 0);
            if (n < 0)
                error("ERROR reading from socket");
             
            if(strlen(buffer) == 0) 
                continue;
            
            printf("REQUEST: %s\n", buffer);
            
            HttpResponseGenerator respGen;
            const char * response_header = respGen.generate_response_header(buffer);
            send(newsockfd, response_header, strlen(response_header), 0);
            
            HttpReq * httpParsedReq = respGen.get_parsed_req();
            send_response(httpParsedReq -> url_path, newsockfd);
            
            printf("RESPONSE SENT\n");

            close(newsockfd);
            exit(EXIT_SUCCESS);

        } else {
            int stat = -1;
            pid_t t = waitpid(pid, &stat, WNOHANG);
            std::cout << "Child process exit status in parent: " << stat << std::endl;
            close(newsockfd);
        }
    }
}

void SocketConnection::send_response(std::string urlPath, int fd)
{
    ServerFileSystem server_fs;
   
    std::cout << "Url path : " << urlPath << std::endl;
    if(server_fs.check_if_URL_exists(urlPath)) {
        
        if(!urlPath.compare("/")) {
            write_to_socket("/learnee.html", fd);
        } else {
            write_to_socket(urlPath, fd);
        }
        
    } else {
        
        write_to_socket("/404.html", fd);
    }
}

void SocketConnection::write_to_socket(std::string urlPath, int fd)
{
    int n;
    ServerFileSystem server_fs;

    std::ifstream file(server_fs.get_absolute_path(urlPath).c_str());
    file.seekg(0, std::ifstream::beg);
    
    while(file.tellg() != -1)
    {
        char *p = new char[10240];
        
        bzero(p, 10240);
        file.read(p, 10240);
    
        n = send(fd, p, 10240, SO_NOSIGPIPE);
        
        if (n < 0) {
            error("ERROR writing to socket");
        } 
        
        delete p;
    }
    
    file.close();
}

void SocketConnection::close_fd()
{
    close(sockfd);
}

void SocketConnection::error(const char *msg)
{
    printf("Error occured\n");
    perror(msg);    
    exit(1);
}
