//
// Created by dtchorni on 26/05/19.
//

#ifndef SUDOKU_ARGUMENTS_HPP
#define SUDOKU_ARGUMENTS_HPP

const float VERSION = 0.1;


struct Arguments {
    const int version = 0.1;
    int sqSize = 3;
    int algorithm = 0;
    bool verbose = false;
    bool reset = false;
    bool ignore = false;

    void setArgs(int, char **);
};

extern Arguments args;


void dialogue();


#endif //SUDOKU_ARGUMENTS_HPP
