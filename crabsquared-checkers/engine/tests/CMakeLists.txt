cmake_minimum_required(VERSION 3.17)
project(crabsquared-checkers)

macro(addTest name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} engine)
    add_test(${name} ${name})
endmacro()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process
    --verbose
    --output-on-failure
)

addTest(test_8x8_forward_only)
addTest(test_8x8_clinch)
addTest(test_8x8_single_capture)
addTest(test_8x8_multi_capture)
#addTest(test_8x8_king_nocapture)
#addTest(test_8x8_king_captures)
#addTest(test_8x8)
#addTest(test_edgecase)
#addTest(test_small)
#addTest(test_not_rectangular)
#addTest(test_not_8x8)
#addTest(test_full_generality)
