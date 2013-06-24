//
//  HttpRequestParser.cpp
//  Web Server
//
//  Created by Krishna Chaitanya on 10/29/12.
//  Copyright (c) 2012 Sourcebits. All rights reserved.
//

#include <iostream>
#include "HttpRequestParser.h"

HttpReq* HttpRequestParser::parseRequest(char *req)
{
    HttpReq *httpReq = new HttpReq();

    httpReq -> length = strlen(req);    
     
    char *reqFirstLine, *temp, *urlPath;
    
    reqFirstLine = strtok(req, "\n");                                                                                                             
          
    if(reqFirstLine != NULL)
        printf("HTTP Request first line: %s\n", reqFirstLine);
        
    httpReq -> http_method = strtok(reqFirstLine, " ");
         
    if((httpReq -> http_method) != NULL)
    {
        printf("Request method: %s\n", httpReq -> http_method);
        
        temp = strtok(NULL, " ");
        
        if(!strcmp(temp, "/"))
        {
            httpReq -> ifRoot = true;
            
            //char *tmp = "html";
            char *tmp = new char[4];
            tmp = strcpy(tmp, "html");
            
            httpReq ->extension = tmp;
            
            urlPath = new char[2];
            urlPath = strcpy(urlPath, "/");
            
        } else {
            
            httpReq -> ifRoot = false;
            
            urlPath = new char[MAX_FILE_NAME_SIZE];
            
            char *tmp;
            tmp = strtok(temp, ".");
            
            if(tmp != NULL) {
                
                httpReq -> extension = strtok(NULL, ".");
                
                if(httpReq -> extension == NULL) {
                    
                    char *tmp = new char[2];
                    tmp = strcpy(tmp, "");
                    
                    httpReq -> extension = tmp;
                    
                    urlPath = strcpy(urlPath, temp);
                    
                } else {
                        
                    urlPath = strcpy(urlPath, temp);
                    urlPath = strcat(urlPath, ".");               
                    urlPath = strcat(urlPath, httpReq -> extension);
                }
            }
        }
            
        printf("Path of file: %s, %d\n", temp, httpReq -> ifRoot);
    }  
        
    httpReq -> url_path = urlPath;
    
    std::cout << "File type: " << httpReq -> extension << std::endl;
    std::cout << "URL path: " << httpReq -> url_path << std::endl;
    
    return httpReq;
}
