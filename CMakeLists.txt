cmake_minimum_required(VERSION 3.20)
project(APathfiding CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app
    src/main.cpp
    src/utils/log.cpp
)

target_include_directories(app PRIVATE src)