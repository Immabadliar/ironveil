#include <iostream>
#include "../utils/logger.hpp"
// Standard Library
#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>

// ZeroMQ
#include <zmq.hpp>

// gRPC & Protobuf
#include <google/protobuf/util/json_util.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
// Your generated proto file
#include "your_service.grpc.pb.h"

// Crypto++
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>

// OpenSSL
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

// Capstone
#include <capstone/capstone.h>

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
    IronLog::warn("User on unknown OS");
#endif

    IronLog::close();
    return 0;
}
