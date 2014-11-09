#include <iostream>
#include "http_client.h"
#include "http_request.h"

int main() {
    typedef botnet::http::http_request http_request;
    typedef botnet::http::http_client http_client;

    http_request *http_req = new http_request(botnet::http::GET);
    http_request::headers header;
    header.add("Host", "www.cpqd.com.br");
    http_req->setHeaders(header);

    http_client *http_c = new http_client("www.cpqd.com.br");
    http_c->request(http_req);

	std::cout << http_c->getContent() << '\n';
	return 0;
}