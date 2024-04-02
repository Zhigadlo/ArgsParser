cmake_minimum_required(VERSION 3.28)

project(tests LANGUAGES CXX)

add_executable(tests main.cpp)

target_link_libraries(tests PRIVATE parser Catch2::Catch2WithMain)

catch_discover_tests(tests)