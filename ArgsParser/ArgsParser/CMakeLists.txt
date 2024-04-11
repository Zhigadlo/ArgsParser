cmake_minimum_required(VERSION 3.28)

project(ArgsParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    add_compile_options(/permissive-)
    add_compile_options(/W3)
    add_compile_options(/utf-8)
endif()

find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(src/args)
add_subdirectory(src/parser)
add_subdirectory(src/results)
add_subdirectory(src/utils)
add_subdirectory(src/validators)

include(CTest)
include(Catch)
enable_testing()

add_subdirectory(tests)

add_executable(ArgsParser main.cpp)

target_include_directories(ArgsParser PRIVATE src/args src/parser src/results src/utils src/validators tests)
target_include_directories(tests PRIVATE src/args src/parser src/results src/utils src/validators Catch2::Catch2WithMain)
target_link_libraries(ArgsParser PRIVATE args parser results validators)
target_link_libraries(tests PRIVATE args parser results validators Catch2::Catch2WithMain)