cmake_minimum_required(VERSION 3.10)
project(utils)

add_library(utils INTERFACE)

# Add include directories for the library
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add the header files to the library
target_sources(utils INTERFACE
    constants.hpp
    converter.hpp
)

# Install the header files
install(FILES
    constants.hpp
    converter.hpp
    DESTINATION include/utils
)