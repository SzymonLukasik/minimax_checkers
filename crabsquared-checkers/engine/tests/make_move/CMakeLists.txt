cmake_minimum_required(VERSION 3.17)
project(crabsquared-checkers)

include_directories(../..)
include_directories(..)

add_custom_target(check_make_move COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process
    --verbose
    --output-on-failure
)

addTest(single_capture)
addTest(non_capture)
addTest(multiple_captures)
