#include "logger.hpp"
#include <cstring> // For strlen

namespace IronLog
{
    std::ofstream logfile;

    void init(const std::string &filename)
    {
        logfile.open(filename, std::ios::app);
    }

    void log(const std::string &message, LogLevel level)
    {
        if (!logfile.is_open())
            return;

        std::string prefix;
        switch (level)
        {
        case LogLevel::INFO:
            prefix = "[INFO] ";
            break;
        case LogLevel::WARNING:
            prefix = "[WARN] ";
            break;
        case LogLevel::ERROR:
            prefix = "[ERROR] ";
            break;
        }

        time_t now = std::time(nullptr);
        char *dt = std::ctime(&now);
        dt[strlen(dt) - 1] = '\0'; // Remove trailing newline

        logfile << dt << " " << prefix << message << std::endl;
    }

    void close()
    {
        if (logfile.is_open())
            logfile.close();
    }
}
