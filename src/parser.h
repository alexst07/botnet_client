#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.h"

namespace botnet {
    typedef int(*command)(std::string p);
    typedef std::map<std::string, command> cmd_map;

    /**
    * command should have this format
    * key_1:value_1
    * key_2:value_2
    * .
    * .
    * .
    * key_n:value_n
    */
    class parser {
        std::string src_;
        std::vector<std::string> arr_;
        cmd_map funcs_;
    public:
        parser(std::vector<std::string>& arr);
        void execute();
    };
}