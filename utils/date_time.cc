#include "headers/date_time.h"
#include <time.h>
#include <stdio.h>

std::string CurrentDateTime::date_and_time()
{
    time_t now = time(0);
    struct tm tstruct;
    std::string buf;
    tstruct = *localtime(&now); // i really hate using c functions
    
}

//  CurrentDateTime() : date_and_time(NULL) {}
//     std::string date_and_time;
//     std::string date_and_time();
//     std::string date_and_time(std::string format);
//     std::string date_and_time(std::string value, std::string format);

std::string CurrentDateTime::date_and_time(std::string format)
{
    return NULL;
}

std::string CurrentDateTime::date_and_time(std::string format, std::string value)
{
}

std::string CurrentDateTime::get_date_and_time()
{
}