cmake_minimum_required(VERSION 3.28)

project(results LANGUAGES CXX)

set(SOURCE_FILES
	HandleResult.hpp
	HandleResult.cpp
)

add_library(results ${SOURCE_FILES})

target_include_directories(results PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(results PUBLIC cxx_std_17)