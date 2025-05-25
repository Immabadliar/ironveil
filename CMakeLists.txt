cmake_minimum_required(VERSION 3.16)
project(AntiCheatMac)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where Homebrew installs packages
set(HOMEBREW_PREFIX "/opt/homebrew")

# Boost
set(BOOST_ROOT "${HOMEBREW_PREFIX}/opt/boost")
set(Boost_NO_SYSTEM_PATHS TRUE)
find_package(Boost REQUIRED)

# ZeroMQ
find_path(ZEROMQ_INCLUDE_DIR zmq.hpp PATHS "${HOMEBREW_PREFIX}/include")
find_library(ZEROMQ_LIBRARY NAMES zmq PATHS "${HOMEBREW_PREFIX}/lib")

# gRPC
find_package(gRPC CONFIG REQUIRED) # assumes gRPC installed with CMake config files

# Crypto++
find_path(CRYPTOPP_INCLUDE_DIR cryptopp/cryptlib.h PATHS "${HOMEBREW_PREFIX}/include")
find_library(CRYPTOPP_LIBRARY NAMES cryptopp PATHS "${HOMEBREW_PREFIX}/lib")

# OpenSSL
find_package(OpenSSL REQUIRED)

# Capstone
find_path(CAPSTONE_INCLUDE_DIR capstone/capstone.h PATHS "${HOMEBREW_PREFIX}/include")
find_library(CAPSTONE_LIBRARY NAMES capstone PATHS "${HOMEBREW_PREFIX}/lib")

# Add executable
add_executable(anti_cheat main.cpp)

# Include directories
target_include_directories(anti_cheat PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${ZEROMQ_INCLUDE_DIR}
    ${CRYPTOPP_INCLUDE_DIR}
    ${OpenSSL_INCLUDE_DIR}
    ${CAPSTONE_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(anti_cheat PRIVATE
    ${ZEROMQ_LIBRARY}
    gRPC::grpc++
    ${CRYPTOPP_LIBRARY}
    OpenSSL::SSL
    OpenSSL::Crypto
    ${CAPSTONE_LIBRARY}
)

# Additional compile options if needed
target_compile_options(anti_cheat PRIVATE -Wall -Wextra)
