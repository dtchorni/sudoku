//
// Created by dtchorni on 28/05/19.
//

#include <iostream>
#include <cstring>
#include "Arguments.hpp"


void dialogue() {
    std::cout << "Sudoku Generator " << VERSION <<
              "\n Flags: \n"
              "\t-h : print dialogue\n"
              "\t-v : verbose printing\n"
              "\t-r : reset when algorithm fails, and try again until a valid sudoku is made\n"
              "\t-i : ignores validation at each step, until end.\n"
              "\t-s [i] : size of single square of sudoku grid\n"
              "\t-a [i] : algorithm option (please see the README for options)" << std::endl;
    std::exit(0);
}

void Arguments::setArgs(int c, char **v) {
    for (int i = 1; i < c; ++i) {
        if (strcmp(v[i], "-h")==0) dialogue();
        else if (strcmp(v[i], "-v")==0) args.verbose = !args.verbose;
        else if (strcmp(v[i], "-r")==0) args.reset = !args.reset;
        else if (strcmp(v[i], "-i")==0) args.ignore = !args.ignore;
        else if (strcmp(v[i], "-s")==0) {
            ++i;
            if (i < c) args.sqSize = atoi(v[i]);
            else {
                std::cerr << "Missing integer argument [i]" << std::endl;
                std::exit(1);
            }
        } else if (strcmp(v[i], "-a")==0) {
            ++i;
            if (i < c) args.algorithm = atoi(v[i]);
            else {
                std::cerr << "Missing integer argument [i]" << std::endl;
                std::exit(1);
            }
        } else {
            std::cerr << "Unrecognized flag: " << v[i] << ". Please see dialogue (-h) for more help." << std::endl;
            std::exit(1);
        }
    }
}