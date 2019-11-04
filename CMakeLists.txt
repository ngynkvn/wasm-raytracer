cmake_minimum_required(VERSION 3.10)

# set the project name
project(Raytracer)
# Specify C++17
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(raytracer main.cpp)

## Link libraries
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(raytracer ${PNG_LIBRARY})