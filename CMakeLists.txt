cmake_minimum_required(VERSION 3.9)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(sudoku
        Grid.cc
        Grid.h
        NumberRef.h
        Tile.cc
        Tile.h Sudoku.cpp Sudoku.hpp Filler.cpp Filler.hpp main.cpp EntangledPair.cpp EntangledPair.hpp)
