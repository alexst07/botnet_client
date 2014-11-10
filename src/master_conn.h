#ifndef BOTNET_MASTER_CONN_H_
#define BOTNET_MASTER_CONN_H_

#include <iostream>

namespace botnet {
    class master_conn {
    public:
        master_conn();

        int keyGen();
        void setKeyServer(int key);
        std::string encrypt(std::string str);
        std::string decrypt(std::string str);
    };
}

#endif  // BOTNET_MASTER_CONN_H_