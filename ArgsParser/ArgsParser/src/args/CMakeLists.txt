cmake_minimum_required(VERSION 3.28)

project(args LANGUAGES CXX)

set(SOURCE_FILES
	EmptyArg.hpp
	EmptyArg.cpp
	BoolArg.hpp
	BoolArg.cpp
	IntArg.hpp
	IntArg.cpp
	StringArg.hpp
	StringArg.cpp
	MultiIntArg.hpp
	MultiIntArg.cpp
	MultiEmptyArg.hpp
	MultiEmptyArg.cpp
	MultiStringArg.hpp
	MultiStringArg.cpp
	
)

add_library(args ${SOURCE_FILES})

target_include_directories(args PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args PUBLIC cxx_std_17)