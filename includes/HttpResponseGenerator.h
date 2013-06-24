//
//  HttpResponseGenerator.h
//  Web Server
//
//  Created by Krishna Chaitanya on 10/31/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#ifndef Web_Server_HttpResponseGenerator_h
#define Web_Server_HttpResponseGenerator_h

#include <iostream>
#include <ctime>
#include <sstream>

#include "SocketConnection.h"
#include "ServerFileSystem.h"
#include "constants.h"
#include "statuscodes.h"

class HttpResponseGenerator
{
    private:
    
        HttpReq * parsed_req;
        const char * get_header_url_found(HttpReq *req);
        const char * get_header_url_not_found(HttpReq *req);
    
    public:

        const char * generate_response_header(char * request);
        HttpReq * get_parsed_req();
};

#endif
