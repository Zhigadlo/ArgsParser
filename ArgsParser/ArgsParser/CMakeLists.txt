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

add_subdirectory(src/abstractions)
add_subdirectory(src/args)
add_subdirectory(src/parser)
add_subdirectory(src/results)
add_subdirectory(src/constants)

add_executable(ArgsParser main.cpp)

target_include_directories(ArgsParser PRIVATE src/abstractions src/args src/parser src/results src/constants)
target_link_libraries(ArgsParser abstractions args parser results)