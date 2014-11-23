#include <iostream>
#include <string>
#include <vector>
#include <map>

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
        cmd_map funcs_;
        std::vector<std::string> split(std::string str, std::string sep);
    public:
        parser(std::string src);
        void execute();
    };
}