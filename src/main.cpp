#include <iostream>
#include "../utils/logger.hpp"

void runCoreLogicWindows()
{
    IronLog::log("Running Windows core logic");
}

void runCoreLogicMac()
{
    IronLog::log("Running MacOS core logic");
}

void runCoreLogicLinux()
{
    IronLog::log("Running Linux core logic");
}

int main()
{
    IronLog::init("app.log");
    std::cout << "Screw you, spdlog!" << '\n';

#if defined(_WIN32)
    IronLog::log("User on WIN32");
    runCoreLogicWindows();
#elif defined(__APPLE__)
    IronLog::log("User on MACOS");
    runCoreLogicMac();
#elif defined(__linux__)
    IronLog::log("User on Linux");
    runCoreLogicLinux();
#else
    IronLog::log("User on unknown OS");
#endif

    IronLog::close();
    return 0;
}
