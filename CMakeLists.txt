cmake_minimum_required(VERSION 3.9)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(sudoku
        Sudoku.cpp Sudoku.hpp Filler.cpp Filler.hpp main.cpp EntangledPair.cpp EntangledPair.hpp Arguments.hpp Arguments.cpp Tracer.cpp Tracer.hpp)
