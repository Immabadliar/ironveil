cmake_minimum_required(VERSION 3.20)
project(ironveil)

set(CMAKE_CXX_STANDARD 20)

# Include libraries
find_package(Boost REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
)

add_executable(ironveil
    src/main.cpp
)

target_link_libraries(ironveil
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    Threads::Threads
)
