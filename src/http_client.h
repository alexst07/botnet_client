#ifndef BOTNET_HTTP_CLIENT_H_
#define BOTNET_HTTP_CLIENT_H_

#include <iostream>
#include <map>
#include <string>

#include "http_request.h"

namespace botnet {
    namespace http {
        class http_client {
        public:
            http_client(std::string url, int port) : _url(url), _port(port)
            {}

            bool request(http_request *req);
            std::string getContent() const {
                return _code;
            }

        private:
            std::string _url;
            std::string _code;
            int _port;
            std::map<std::string, std::string> hmap;
        };
    }
}

#endif  // BOTNET_HTTP_CLIENT_H_