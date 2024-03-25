cmake_minimum_required(VERSION 3.28)

project(Example LANGUAGES CXX)

add_executable(Example main.cpp)

target_compile_features(Example PUBLIC cxx_std_17)