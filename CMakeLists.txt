cmake_minimum_required(VERSION 3.26)
project(cpp1_battleshiphwGV)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src)
include_directories(tests)

add_executable(cpp1_battleshiphwGV
        lib/board.h
        lib/consts.h
        lib/game.h
        src/board.cpp
        src/game.cpp
        src/main.cpp
        tests/tests.cpp
        README.md)
