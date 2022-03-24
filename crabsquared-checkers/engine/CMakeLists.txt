cmake_minimum_required (VERSION 3.1)
project (crabsquared-checkers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

add_executable(engine engine.cpp)

# install(TARGETS DESTINATION .)  
