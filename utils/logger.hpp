#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

namespace IronLog
{
    enum class LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };

    void init(const std::string &filename);
    void log(const std::string &message, LogLevel level = LogLevel::INFO);
    void close();
}

#endif
