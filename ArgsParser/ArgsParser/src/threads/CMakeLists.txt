cmake_minimum_required(VERSION 3.28)

project(threads LANGUAGES CXX)

set(SOURCE_FILES
	ThreadPool.hpp
	ThreadPool.cpp
)

add_library(threads ${SOURCE_FILES})

target_include_directories(threads PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(threads PUBLIC cxx_std_17)