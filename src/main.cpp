#include <iostream>
#include <fstream>
#include "../utils/logger.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>

void onCheatDetected(const std::string& cheatName) {
    IronLog::log("Cheat detected: " + cheatName, IronLog::LogLevel::WARNING);
}

bool fileContainsPattern(const boost::filesystem::path& filePath, const boost::regex& pattern) {
    std::ifstream file(filePath.string());
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (boost::regex_search(line, pattern)) {
            return true;
        }
    }
    return false;
}

void scanDirectoryForCheats(const boost::filesystem::path& dirPath, const boost::regex& cheatPattern) {
    try {
        for (auto& entry : boost::filesystem::recursive_directory_iterator(dirPath)) {
            if (boost::filesystem::is_regular_file(entry.path())) {
                if (fileContainsPattern(entry.path(), cheatPattern)) {
                    onCheatDetected(entry.path().string());
                }
            }
        }
    }
    catch (const boost::filesystem::filesystem_error& ex) {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }
}




int main()
{
    IronLog::init("app.log");
    std::cout << "Screw you, spdlog!" << '\n';
#if defined(_WIN32)
    IronLog::log("User on WIN32");
    const char* userProfile = std::getenv("USERPROFILE");  // Windows
    if (!userProfile) {
        std::cerr << "Could not find USERPROFILE environment variable." << std::endl;
        return 1;
    }

    boost::filesystem::path userFolder(userProfile);
    std::cout << "Scanning folder: " << userFolder.string() << std::endl;

    boost::regex cheatRegex("aimbot|wallhack|cheat|hack", boost::regex_constants::icase);
    scanDirectoryForCheats(userFolder, cheatRegex);
#elif defined(__APPLE__)
    IronLog::log("User on MACOS");
#elif defined(__linux__)
    IronLog::log("User on Linux");;
#else
    IronLog::warn("User on unknown OS");
#endif


    IronLog::close();
    return 0;
}
