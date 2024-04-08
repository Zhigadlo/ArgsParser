cmake_minimum_required(VERSION 3.28)

project(args LANGUAGES CXX)

set(SOURCE_FILES
	Args.hpp
	Args.cpp
)

add_library(args ${SOURCE_FILES})

target_include_directories(args PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args PUBLIC cxx_std_17)