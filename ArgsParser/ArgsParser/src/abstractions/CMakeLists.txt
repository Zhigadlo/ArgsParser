cmake_minimum_required(VERSION 3.28)

project(abstractions LANGUAGES CXX)

set(SOURCE_FILES
	Arg.cpp
	Arg.hpp
	ValueArg.cpp
	ValueArg.hpp
)

add_library(abstractions ${SOURCE_FILES})

target_include_directories(abstractions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(abstractions PUBLIC cxx_std_17)