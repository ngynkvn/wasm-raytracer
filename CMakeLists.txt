cmake_minimum_required(VERSION 3.10)

# set the project name
project(Raytracer)
# Specify C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)


# add the executable
add_executable(raytracer main.cpp raytracer.cpp ostreams.cpp scene_parser.cpp)

## Link libraries
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(raytracer ${PNG_LIBRARY})
