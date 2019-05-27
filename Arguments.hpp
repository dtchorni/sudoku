//
// Created by dtchorni on 26/05/19.
//

#ifndef SUDOKU_ARGUMENTS_HPP
#define SUDOKU_ARGUMENTS_HPP


struct Arguments {
    const int version =0.1;
    int sq_size=3;
    int algorithm=0;
    bool verbose=false;

};

extern Arguments args;

#endif //SUDOKU_ARGUMENTS_HPP
