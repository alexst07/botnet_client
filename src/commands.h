#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "http_request.h"
#include "http_client.h"

namespace botnet {
    typedef http::http_request http_request;
    typedef http::http_client http_client;

    int http_req(std::string url);
    int get_pcname(std::string s);
}