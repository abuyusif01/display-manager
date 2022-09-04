#include "headers/date_time.h"
#include <time.h>
#include <stdio.h>
#include <string>

std::string CurrentDateTime::date_and_time()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now); // i really hate using c functions
    strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);
    return buf;
}

std::string CurrentDateTime::date_and_time(std::string format)
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now); // i really hate using c functions
    strftime(buf, sizeof(buf), format.c_str(), &tstruct);
    return buf;
}
