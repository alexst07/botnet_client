#ifndef BOTNET_HTTP_REQ_H_
#define BOTNET_HTTP_REQ_H_

#include <iostream>
#include <string>
#include <list>

namespace botnet {
    namespace http {
        enum method {
            GET,
            POST
        };

        class http_request {
        public:
            class headers {
            public:
                headers& operator=(const headers& other) {
                    _head = other._head;
                    return *this;
                }

                void add(std::string key, std::string value) {
                    line_h l;
                    l.key = key;
                    l.value = value;
                    _head.push_back(l);
                }
                std::string getAll() {
                    std::string str_head = std::string("");
                    for (auto const &l : _head) {
                        str_head += l.key + ": " + l.value + "\r\n";
                    }
                    str_head += "\r\n";
                    return str_head;
                }

            private:
                struct line_h {
                    std::string key;
                    std::string value;
                };

                std::list<line_h> _head;
            };

            http_request(method m) :_m(m)
            {
                _path = "/";
            }

            method getMethod() const {
                return this->_m;
            }

            void setPath(std::string &path) {
                _path = path;
            }

            std::string getPath() const {
                return _path;
            }

            void setHeaders(headers &h) {
                _h = h;
            }

            headers getHeaders() const {
                headers h = _h;
                return h;
            }

        private:
            method _m;
            headers _h;
            std::string _path;
        };
    }
}

#endif  // BOTNET_HTTP_REQ_H_