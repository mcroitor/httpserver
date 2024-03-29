# CMake version check
cmake_minimum_required(VERSION 3.8)

# Create project "server"
project(httpserver
    VERSION 1.0
    DESCRIPTION "Simple HTTP server"
    LANGUAGES CXX
)

# Enable c++17 standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# All source files are stored in the src directory
file(GLOB SOURCE_FILES src/*.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(httpserver ${SOURCE_FILES})

# set include dir
set(INCLUDE_DIR include/)
target_include_directories(httpserver PRIVATE ${INCLUDE_DIR})
target_link_libraries(httpserver -static)

# PVS Studio analysis
# include (pvs/PVS-Studio.cmake)
# pvs_studio_add_target(TARGET server.analyze ALL
#                      OUTPUT FORMAT errorfile
#                      ANALYZE ${PROJECT_NAME} server.lib:src
#                      LOG target.err)