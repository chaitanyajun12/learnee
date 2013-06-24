//
//  HttpResponseGenerator.cpp
//  Web Server
//
//  Created by Krishna Chaitanya on 10/31/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#include "HttpResponseGenerator.h"

const char * HttpResponseGenerator::generate_response_header(char * request)
{
    HttpRequestParser parseReq;
    HttpReq *req = parseReq.parseRequest(request);
    ServerFileSystem server_fs;
    
    parsed_req = req;
    
    std::string response = "";
        
    if(server_fs.check_if_URL_exists(req -> url_path)) {
        response = get_header_url_found(req);
    } else {
        response = get_header_url_not_found(req);
    }
    
    std::cout << "Response header: " << response << std::endl;
    
    return response.c_str();
}

const char * HttpResponseGenerator::get_header_url_found(HttpReq *req) {
    
    ServerFileSystem server_fs;
    
    time_t now = time(0);
    tm *localtm = localtime(&now);
    std::string response = "";
    
    int file_size = server_fs.get_file_size(req -> url_path);
    std::string content_type = server_fs.get_content_type(req -> extension);
    
    std::ostringstream size;
    size << file_size;
    
    response = response + HTTP_VERSION_1_1;
    response = response + HTTP_200;
    response = response + NEW_LINE;
    
    response = response + "Date: ";
    response = response + asctime(localtm);
        
    response = response + "Content-Type: ";
    response = response + content_type;
    response = response + NEW_LINE;
        
    response = response + "Content-Length: ";
    response = response + size.str();
    response = response + NEW_LINE;
    
    response = response + "Server: ";
    response = response + SERVER_NAME;
    response = response + NEW_LINE;
    
    response = response + NEW_LINE;
    
    return response.c_str();
}

const char * HttpResponseGenerator::get_header_url_not_found(HttpReq *req) {
    
    ServerFileSystem server_fs;

    time_t now = time(0);
    tm *localtm = localtime(&now);
    std::string response = "";
    
    int file_size = server_fs.get_file_size("/404.html");
    
    file_size = file_size + strlen(req -> url_path);
    
    std::ostringstream size;
    size << file_size;

    response = response + HTTP_VERSION_1_1;
    response = response + HTTP_404;
    response = response + NEW_LINE;
    
    response = response + "Date: ";
    response = response + asctime(localtm);
    
    response = response + "Content-Type: ";
    response = response + "text/html";
    response = response + NEW_LINE;
    
    response = response + "Content-Length: ";
    response = response + size.str();
    response = response + NEW_LINE;

    response = response + "Server: ";
    response = response + SERVER_NAME;
    response = response + NEW_LINE;

    response = response + NEW_LINE;
    
    return response.c_str();
}

HttpReq * HttpResponseGenerator::get_parsed_req()
{
    return parsed_req;
}



