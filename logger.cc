#include "headers/logger.h"
#include "utils/headers/date_time.h"
#include <fstream>

Logger::Logger()
{
    // this gonna be nothing for now
}

Logger::Logger(int type, std::string content, std::string location)
{
    CurrentDateTime *date_and_time;

    this->type = type;
    this->content = content;
    this->location = location;      // technically the file name for now
    std::ofstream logger(location); // open file with the given name

    switch (type)
    {
    case 1:
        logger << this->error << date_and_time->date_and_time() << this->clean(content);
        break;
    case 2:
        logger << this->warning << date_and_time->date_and_time() << this->clean(content);
        break;
    case 3:
        logger << this->info << date_and_time->date_and_time() << this->clean(content);
        break;
    default:
        logger << this->unknown << date_and_time->date_and_time() << this->clean(content);
    }

    logger.close();
}

std::string Logger::clean(std::string content)
{
    return content.insert(0, " ");
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
        this->type = -1;
    }
}