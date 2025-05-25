#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>
#include <string>

#include "../utils/logger.hpp"

void onCheatDetected(const std::string& cheatName) {
    IronLog::log("Cheat detected: " + cheatName, IronLog::LogLevel::WARNING);
}

bool fileContainsPattern(const std::filesystem::path& filePath, const std::regex& pattern) {
    std::ifstream file(filePath);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (std::regex_search(line, pattern)) {
            return true;
        }
    }
    return false;
}

void scanDirectoryForCheats(const std::filesystem::path& dirPath, const std::regex& cheatPattern) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                if (fileContainsPattern(entry.path(), cheatPattern)) {
                    onCheatDetected(entry.path().string());
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }
}

int main() {
    IronLog::init("app.log");
    std::cout << "Screw you, spdlog!" << '\n';

#if defined(_WIN32)
    IronLog::log("User on WIN32");
    const char* userProfile = std::getenv("USERPROFILE");
    if (!userProfile) {
        std::cerr << "Could not find USERPROFILE environment variable." << std::endl;
        return 1;
    }

    std::filesystem::path userFolder(userProfile);
    std::cout << "Scanning folder: " << userFolder.string() << std::endl;

    std::regex cheatRegex(R"(aimbot|wallhack|cheat|hack)", std::regex::icase);
    scanDirectoryForCheats(userFolder, cheatRegex);
#elif defined(__APPLE__)
    IronLog::log("User on MACOS");
#elif defined(__linux__)
    IronLog::log("User on Linux");
#else
    IronLog::warn("User on unknown OS");
#endif

    IronLog::close();
    return 0;
}
