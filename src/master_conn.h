#ifndef BOTNET_MASTER_CONN_H_
#define BOTNET_MASTER_CONN_H_

#include <iostream>
#include <string>

namespace botnet {
    class master_conn {
        std::string client_id;
        int client_key;
        std::string hash_key;

        std::string client_key_gen();
        std::string confirm();
        std::string expand_key(std::string str_key);
    public:
        master_conn();
        

        int keyGen();
        void setKeyServer(int key);
        std::string encrypt(std::string str);
        std::string decrypt(std::string str);
    };
}

#endif  // BOTNET_MASTER_CONN_H_