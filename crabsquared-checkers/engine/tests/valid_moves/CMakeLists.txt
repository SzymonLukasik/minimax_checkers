cmake_minimum_required(VERSION 3.17)
project(crabsquared-checkers)

include_directories(../..)
include_directories(..)

add_custom_target(check_valid_moves COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process
    --verbose
    --output-on-failure
)

addTest(test_8x8_forward_only)
addTest(test_8x8_clinch)
addTest(test_8x8_single_capture)
addTest(test_8x8_multi_capture)
addTest(test_8x8)
addTest(test_edgecase)
addTest(test_small)
addTest(test_not_rectangular)
