cmake_minimum_required(VERSION 3.2)
set(This rotation-logger)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

include_directories(
  include
)

set(Sources
  src/rotation-logger.cc
)

add_library(${This} ${Sources})
# target_include_directories(${This} PUBLIC 
#   ${CMAKE_CURRENT_SOURCE_DIR}
# )