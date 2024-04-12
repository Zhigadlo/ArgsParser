cmake_minimum_required(VERSION 3.28)

project(catalogs LANGUAGES CXX)

set(SOURCE_FILES
	Catalog.hpp
	Catalog.cpp
)

add_library(catalogs ${SOURCE_FILES})

target_include_directories(catalogs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(catalogs PUBLIC cxx_std_17)