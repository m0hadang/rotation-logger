cmake_minimum_required(VERSION 3.2)
set(This root-project)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(rotation-logger)
add_subdirectory(googletest)
add_subdirectory(example)
add_subdirectory(test)