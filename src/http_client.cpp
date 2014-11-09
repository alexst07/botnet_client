#include <winsock2.h>
#include <windows.h>
#include <iostream>

#include "http_request.h"
#include "http_client.h"

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
            char buffer[BUFFER_LEN + 1];

            _code = "";

            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
                return false;

            Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

            struct hostent *host;
            host = gethostbyname(_url.c_str());

            SOCKADDR_IN SockAddr;
            SockAddr.sin_port = htons(80);
            SockAddr.sin_family = AF_INET;
            SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

            connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
            if (req->getMethod() == method::GET)
                str_method = "GET";
            else if (req->getMethod() == method::POST)
                str_method = "POST";

            requisition = str_method + " " + req->getPath() + " HTTP/1.1\r\n";
            requisition += req->getHeaders().getAll();
            std::cout << "Requisition: " << requisition;
            send(Socket, requisition.c_str(), requisition.length(), 0);

            do {
                nrecv = recv(Socket, buffer, BUFFER_LEN, 0);
                if (nrecv == SOCKET_ERROR)
                    return false;
                
                if (nrecv > 0) {
                    buffer[nrecv] = '\0';
                    _code += buffer;
                }

            } while (nrecv > 0);
            
            closesocket(Socket);
            WSACleanup();

            return true;            
        }
    }
}