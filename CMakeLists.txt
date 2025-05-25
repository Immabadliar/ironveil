cmake_minimum_required(VERSION 3.15)

# Project metadata
project(ironveil LANGUAGES CXX)

# Set C++ standard explicitly and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: Set build type if not set (default to Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Enable verbose output for debugging
set(CMAKE_VERBOSE_MAKEFILE ON)

# -----------------------------------------------------------------------------
# Dependencies and packages
# -----------------------------------------------------------------------------

# Protobuf and gRPC packages (required)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Boost libraries (adjust versions and components as needed)
find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem)

# Other useful libraries
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(c-ares REQUIRED)
find_package(RE2 REQUIRED)

# -----------------------------------------------------------------------------
# Proto files and generated sources
# -----------------------------------------------------------------------------

# Directory where proto files live
set(PROTO_DIR "${CMAKE_SOURCE_DIR}/ironveil/proto")

# List your proto files here explicitly
set(PROTO_FILES
  "${PROTO_DIR}/your_service.proto"
  # Add more proto files if needed
)

# Use protobuf_generate_cpp and grpc_generate_cpp to create source and headers
# These macros generate *_pb.cc/h and *_grpc.pb.cc/h files automatically
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILES})

# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------

# Core application source files (adjust paths as needed)
set(SRC_FILES
  ironveil/src/main.cpp
  # Add other source files here
)

# -----------------------------------------------------------------------------
# Create executable target
# -----------------------------------------------------------------------------

add_executable(anti_cheat
  ${SRC_FILES}
  ${PROTO_SRCS}
  ${PROTO_HDRS}
  ${GRPC_SRCS}
  ${GRPC_HDRS}
)

# -----------------------------------------------------------------------------
# Include directories
# -----------------------------------------------------------------------------

# Include proto generated headers and source directory
target_include_directories(anti_cheat
  PRIVATE
    ${PROTO_DIR}
    ironveil/src
)

# -----------------------------------------------------------------------------
# Link libraries to executable
# -----------------------------------------------------------------------------

target_link_libraries(anti_cheat
  PRIVATE
    protobuf::libprotobuf
    gRPC::grpc++
    Boost::system
    Boost::filesystem
    Threads::Threads
    ZLIB::ZLIB
    OpenSSL::SSL
    OpenSSL::Crypto
    c-ares::cares
    re2::re2
)

# -----------------------------------------------------------------------------
# Compiler options
# -----------------------------------------------------------------------------

target_compile_options(anti_cheat PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

# -----------------------------------------------------------------------------
# Installation rules (optional)
# -----------------------------------------------------------------------------

install(TARGETS anti_cheat
  RUNTIME DESTINATION bin
)

# -----------------------------------------------------------------------------
# Summary output
# -----------------------------------------------------------------------------

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Using protobuf version: ${Protobuf_VERSION}")
message(STATUS "Using gRPC version: ${gRPC_VERSION}")
message(STATUS "Boost version: ${Boost_VERSION}")

