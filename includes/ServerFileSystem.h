//
//  ServerFileSystem.h
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#ifndef Web_Server_ServerFileSystem_h
#define Web_Server_ServerFileSystem_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <fcntl.h>

#include "constants.h"

class ServerFileSystem
{
    public:
        
        bool check_if_URL_exists(std::string url);
        int getFD(std::string url);
        int get_file_size(std::string url);
        const char * get_content_type(std::string extension);
        std::string get_absolute_path(std::string url);
};

#endif
    