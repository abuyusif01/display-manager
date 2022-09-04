#include "headers/logger.h"
#include <fstream>
#include <chrono>
#include <ctime>

Logger::Logger()
{
    // this gonna be nothing for now
}

Logger::Logger(int type, std::string content, std::string location)
{
   

    this->type = type;
    this->content = content;
    this->location = location; // technically the file name for now

    std::ofstream logger(location); // open file with the given name

    // [INFO] 2022-02-10:00: Loggin Failed

    switch (type)
    {
    case 1:
        logger << this->error << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << (now->tm_mday) << "-" << (now->tm_min) << ":" << (now->tm_sec) << content << "\n";
        break;
    case 2:
        logger << this->error << (now->tm_year) << "-" << (now->tm_mon) << "-" << (now->tm_mday) << "-" << (now->tm_min) << ":" << (now->tm_sec) << content << "\n";
        break;
    case 3:
        logger << this->error << (now->tm_year) << "-" << (now->tm_mon) << "-" << (now->tm_mday) << "-" << (now->tm_min) << ":" << (now->tm_sec) << content << "\n";
        break;
    default:
        logger << "[UNKNOWN ERROR TYPE] " << (now->tm_year) << "-" << (now->tm_mon) << "-" << (now->tm_mday) << content << "\n";
    }

    logger.close();
}

std::string Logger::get_content()
{
    return this->content;
}

std::string Logger::get_location()
{
    return this->location;
}
int Logger::get_type()
{
    return this->type;
}

void Logger::set_location(std::string location)
{
    this->location = location;
}

void Logger::set_content(std::string content)
{
    this->content = content;
}

void Logger::set_type(int type)
{

    switch (type)
    {
    case 1:
        this->type = 1;
        break;
    case 2:
        this->type = 2;
        break;
    case 3:
        this->type = 3;
        break;
    default:
        this->type = 1;
    }
}