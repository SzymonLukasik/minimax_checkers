cmake_minimum_required(VERSION 3.1)
project(crabsquared-checkers)

macro(addTest name)
    add_executable(${name} test_driver.cpp ${name}.cpp)
    target_link_libraries(${name} engine)
    add_test(${name} ${name})
endmacro()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process
    --verbose
    --output-on-failure
)

add_subdirectory(make_move)
add_subdirectory(valid_moves)