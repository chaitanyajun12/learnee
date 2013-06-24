//
//  ServerFileSystem.cpp
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#include "ServerFileSystem.h"


bool ServerFileSystem::check_if_URL_exists(std::string urlPath)
{
    std::string localPath = SERVER_ROOT + urlPath;

    std::ifstream file(localPath.c_str()); 
    if(file.is_open()) 
    {
        file.close();
        return true;
    }

    return false;
}

int ServerFileSystem::getFD(std::string urlPath)
{
    int fd = -1;
    std::string localPath = SERVER_ROOT + urlPath;
    
    fd = open(urlPath.c_str(), O_RDONLY);
    
    return fd;
}

const char * ServerFileSystem::get_content_type(std::string extension)
{
    std::string content_type;
    
    if(!extension.compare("html") || !extension.compare("") || !extension.compare("htm")) {
        
        content_type = "text/html";
        
    } else if(!extension.compare("png") || !extension.compare("jpg") || !extension.compare("jpeg") || extension.compare("bmp")) {
        
        content_type = "image";
        content_type = content_type + SEPERATOR;
        content_type = content_type + extension;
    } 
    
    return content_type.c_str();
}
 
int ServerFileSystem::get_file_size(std::string urlPath) 
{
    if(!urlPath.compare("/")) 
        return LOCALHOST_REPONSE_SIZE;
    
    std::string localPath = SERVER_ROOT + urlPath;
    std::ifstream file(localPath.c_str());
    
    if(file.is_open()) {

        file.seekg(0, std::ifstream::end);        
        return file.tellg();
    }
    
    return 0;
}

std::string ServerFileSystem::get_absolute_path(std::string url)
{
    return  SERVER_ROOT + url;
}