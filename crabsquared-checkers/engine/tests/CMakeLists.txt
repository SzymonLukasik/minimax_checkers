cmake_minimum_required(VERSION 3.14.0)
project(crabsquared-checkers)

macro(addTest name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} engine)
    add_test(${name} ${name})
endmacro()

addTest(test_simple_movements)
addTest(test_not_8x8)
