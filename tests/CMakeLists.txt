# compile unit tests for httpserver

# CMake version check
cmake_minimum_required(VERSION 3.8)

# Project name
project(
    httpserver-tests
    LANGUAGES CXX
)

# Enable c++17 standard
set(CMAKE_CXX_STANDARD 17)

# files
set(SOURCE_FILES tests.cpp ../src/lib.cpp ../src/logger.cpp)

# add executable
add_executable(unittests ${SOURCE_FILES})

# set include dir
set(INCLUDE_DIR ../include/)
target_include_directories(unittests PRIVATE ${INCLUDE_DIR})
target_link_libraries(unittests -static)

add_test(NAME unittests COMMAND unittests)