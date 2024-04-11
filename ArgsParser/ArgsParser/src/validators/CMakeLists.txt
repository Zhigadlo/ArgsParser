cmake_minimum_required(VERSION 3.28)

project(validators LANGUAGES CXX)

set(SOURCE_FILES
	Validators.hpp
	Validators.cpp
)

add_library(validators ${SOURCE_FILES})

target_include_directories(validators PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(validators PUBLIC cxx_std_17)