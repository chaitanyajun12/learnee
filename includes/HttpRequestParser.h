//
//  HttpRequestParser.h
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#ifndef Web_Server_HttpRequestParser_h
#define Web_Server_HttpRequestParser_h

#include <cstring>
#include "constants.h"

typedef struct HttpRequest {
    
    char * http_method;
    char * url_path;
    int length;
    char * extension;
    bool ifRoot;
    
}HttpReq;



class HttpRequestParser
{
    public:

        HttpReq* parseRequest(char *request);
};


#endif
