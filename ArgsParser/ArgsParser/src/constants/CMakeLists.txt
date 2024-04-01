add_library(constants INTERFACE)

target_include_directories(constants INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES constants.hpp DESTINATION include/constants)