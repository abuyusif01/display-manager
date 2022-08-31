#ifndef LOGGER_H
#define LOGGER_H
#include <string>

class Logger
{

private:
    std::string location;
    std::string content;
    std::string error = "[ERROR] "; // the spaces here are intentional
    std::string warning = "[WARNING] ";
    std::string info = "[INFO] ";
    int type;

public:
    Logger();
    Logger(int type, std::string content, std::string location);
    void set_location(std::string location);
    void set_content(std::string content);
    void set_type(int type);
    std::string get_location();
    std::string get_content();
    int get_type();
};

#endif // LOGGER_H