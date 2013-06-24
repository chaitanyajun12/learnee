//
//  main.cpp
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#include <iostream>

#include "SocketConnection.h"
#include "constants.h"


int main(int argc, const char * argv[])
{
    int socketFD;
    
    SocketConnection socketConn;
    
    socketFD = socketConn.get_socket_fd();
    socketConn.bind_fd_to_serv_add();
    socketConn.listen_for_connections();
    
    socketConn.close_fd();
    
    return 0;
}

