cmake_minimum_required(VERSION 3.12)

project(
    advent_of_code_cpp
    VERSION 0.1.0
    DESCRIPTION "Advent of Code solutions in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (NOT WIN32)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

file(
    COPY
    ${CMAKE_CURRENT_LIST_DIR}/inputs
    DESTINATION
    ${CMAKE_BINARY_DIR}
)

include_directories(
    src/util
)

add_executable(
    aocc.out
    src/main.cpp
    src/event23/day01.cpp
    src/event23/day02.cpp
    src/event23/day03.cpp
    src/event23/day04.cpp
    src/event23/day05.cpp
    src/event23/day06.cpp
    src/event23/day07.cpp
    src/event23/day08.cpp
    src/util/aoc.h
)
