#ifndef BOTNET_MASTER_CONN_H_
#define BOTNET_MASTER_CONN_H_

#include <iostream>
#include <string>

namespace botnet {
    class master_conn {
        std::string client_id;
        int client_key;
        std::string hash_key;
        int my_rand;
        int count_conn;
        int confirm_msg;

        std::string client_key_gen();
        bool confirm(std::string msg_from_server);
        std::string expand_key(std::string str_key);
        std::string combineKeys(int keyServer);
    public:
        master_conn();

        std::vector<std::string> ask_for_cmd();
        
        int keyGen();
        void setKeyServer(int key);
        std::string encrypt(std::string str);
        std::string decrypt(std::string str);
    };
}

#endif  // BOTNET_MASTER_CONN_H_
