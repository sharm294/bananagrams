cmake_minimum_required(VERSION 3.19.4)

project(bananagrams
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Bananagrams solver"
)

cmake_policy(SET CMP0083 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_LINKER_WRAPPER_FLAG "-Wl,")
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic -pedantic-errors -fno-pie -no-pie")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_subdirectory(src)
add_subdirectory(tests)
