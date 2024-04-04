cmake_minimum_required(VERSION 3.28)

project(tests LANGUAGES CXX)

add_executable(tests main.cpp)

catch_discover_tests(tests)