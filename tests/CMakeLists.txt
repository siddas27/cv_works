cmake_minimum_required(VERSION 3.22)

set(This ExampleTests)

set(Sources
    ExampleTests.cc 
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    utils
)

add_test(
    NAME ${This}
    COMMAND ${This}
)