#ifndef DATE_TIME_H
#define DATE_TIME_H
#include <string>

class CurrentDateTime
{
private:
    // std::string date_and_time;

public:
    CurrentDateTime();
    std::string date_and_time();
    std::string date_and_time(std::string format);
};
#endif // DATE_TIME_H