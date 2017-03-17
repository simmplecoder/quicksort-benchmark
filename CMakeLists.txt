cmake_minimum_required(VERSION 3.6)
project(QuicksortBenchmark)

set(CMAKE_CXX_COMPILER /usr/bin/clang++-5.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /usr/local/include/c++/v1 -stdlib=libc++ -lc++abi -Wall -Wextra -pedantic-errors -std=c++1z")

set(SOURCE_FILES src/main.cpp)
add_executable(QuicksortBenchmark ${SOURCE_FILES})