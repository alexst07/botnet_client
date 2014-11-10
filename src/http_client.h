#ifndef BOTNET_HTTP_CLIENT_H_
#define BOTNET_HTTP_CLIENT_H_

#include <iostream>
#include <string>

#include "http_request.h"

namespace botnet {
    namespace http {
        class http_client {
        public:
            http_client(std::string url) : _url(url)
            {}

            bool request(http_request *req);
            std::string getContent() const {
                return _code;
            }

        private:
            std::string _url;
            std::string _code;
        };
    }
}

#endif  // BOTNET_HTTP_CLIENT_H_