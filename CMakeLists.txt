cmake_minimum_required(VERSION 3.20)
project(AStarPathfinding CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sfml)

add_executable(app
    src/main.cpp
    src/utils/log.cpp
    src/core/grid/grid.cpp
    src/core/astar/astar.cpp
    src/visualization/renderer.cpp
)

target_include_directories(app PRIVATE src)
target_link_libraries(app SFML::Graphics)
