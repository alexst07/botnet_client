#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>

#include "http_request.h"
#include "http_client.h"
#include "utils.h"

#pragma comment(lib,"ws2_32.lib")

namespace botnet {
    namespace http {

#define BUFFER_LEN  1000

        bool http_client::request(http_request *req) {
            WSADATA wsaData;
            SOCKET Socket;
            std::string requisition;
            std::string str_method;
            int nrecv = 0;
            int body_start = 0;
            char buffer[BUFFER_LEN + 1];
            size_t recvd = 0;
            int content_length = 0;
            std::vector<std::string> arr;
            bool get_header = false;
            _code = "";

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
                return false;

            Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            struct hostent *host;
            host = gethostbyname(_url.c_str());

            SOCKADDR_IN SockAddr;
            SockAddr.sin_port = htons(_port);
            SockAddr.sin_family = AF_INET;
            SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

            connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
            if (req->getMethod() == method::GET)
                str_method = "GET";
            else if (req->getMethod() == method::POST)
                str_method = "POST";

            requisition = str_method + " " + req->getPath() + " HTTP/1.1\r\n";
            requisition += req->getHeaders().getAll();

            send(Socket, requisition.c_str(), requisition.length(), 0);

            do {
                
                nrecv = recv(Socket, buffer, BUFFER_LEN, 0);
                if (nrecv == SOCKET_ERROR)
                    return false;
                
                if (nrecv > 0) {
                    buffer[nrecv] = '\0';
                    recvd += nrecv;
                    _code += buffer;
                    body_start = _code.find("\r\n\r\n");
                    if ((body_start != std::string::npos) && (!get_header)) {
                        get_header = true;
                        std::string str_header;
                        str_header = _code.substr(0, body_start);

                        arr = split(str_header, "\r\n");

                        for (size_t i = 0; i < arr.size(); i++) {
                            std::size_t found = arr[i].find_first_of(":");
                            std::size_t found_ln = arr[i].find_first_of("\r\n");
                            if (found != std::string::npos) {
                                std::string key = arr[i].substr(0, found);
                                std::string value = arr[i].substr(found + 2, found_ln);
                                hmap[key] = value;
                                if (key == "Content-Length") {
                                    content_length = std::stoi(value);
                                }
                                    
                            }
                        }
                    }

                    if (nrecv >= (body_start + 4 + content_length))
                        break;
                        
                }

            } while (nrecv > 0);
            
            closesocket(Socket);
            WSACleanup();

            return true;            
        }
    }
}