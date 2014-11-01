#include <iostream>
#include <string>
#include <list>

namespace botnet {
    namespace http {
        enum class method {
            GET,
            POST
        };

        class http_request {
        public:
            http_request(method m) :_m(m)
            {}

            method getMethod() const {
                return this->_m;
            }

            void setPath(std::string path) {
                _path = path;
            }

            std::string getPath() const {
                return _path;
            }

            class headers {
            public:
                void add(std::string key, std::string value) {
                    line_h l;
                    l.key = key;
                    l.value = value;
                    _head.push_back(l);
                }
                std::string getAll() {
                    std::string str_head = std::string("");
                    for (auto const &l : _head) {
                        str_head += l.key + ":" + l.value + "\n\r";
                    }
                    str_head += "\n\r";
                    return str_head;
                }

            private:
                struct line_h {
                    std::string key;
                    std::string value;
                };

                std::list<line_h> _head;
            };
        private:
            method _m;
            std::string _path;
        };
    }
}