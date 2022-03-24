cmake_minimum_required(VERSION 3.1)
project(crabsquared-checkers CXX)

# generate compile commands for linter; disabled since it doesn't work anyway
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

add_executable(engine engine.cpp)

# install(TARGETS DESTINATION .)  
