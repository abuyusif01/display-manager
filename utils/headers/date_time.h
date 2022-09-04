#ifndef DATE_TIME_H
#define DATE_TIME_H
#include <string>

class CurrentDateTime
{
private:
    std::string date_and_time;

public:
    CurrentDateTime() : date_and_time(NULL) {}
    std::string date_and_time();
    std::string date_and_time(std::string format);
    std::string date_and_time(std::string value, std::string format);
    std::string get_date_and_time();
};
#endif // DATE_TIME_H