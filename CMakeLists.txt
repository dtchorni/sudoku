cmake_minimum_required(VERSION 3.9)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(sudoku
        Grid.cc
        Grid.h
        main.cc
        NumberRef.h
        sudoku.h
        Tile.cc
        Tile.h)
