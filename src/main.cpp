#include <iostream>
#include "./utils/logger.hpp"
#include "./core/core.hpp"

int main()
{
    MyLogger::init("app.log");
    std::cout << "Starting Ironveil Anti-Cheat\n";

#if defined(_WIN32)
    MyLogger::log("User on WIN32");
#elif defined(__APPLE__)
    MyLogger::log("User on MACOS");
#elif defined(__linux__)
    MyLogger::log("User on Linux");
#else
    MyLogger::log("User on Unknown OS");
#endif

    runCoreLogic();

    return 0;
}
