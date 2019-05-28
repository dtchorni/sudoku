


#include <iostream>

#include "Sudoku.hpp"
#include "Filler.hpp"
#include "Arguments.hpp"


//TODO: Implement step back infrastructure to easily correct errors
//TODO: Implement a better UI
//TODO: Create command line arguments to facilitate scripts
//TODO: Ensure there is a verbosity option
//TODO: Create an export method
//TODO: Do an analysis on all algorithms implemented, perhaps create a suite to do this within the program
//TODO: would be interesting to attempt to export each step of generation into a gif or video
//TODO: DOCUMENT

Arguments args = Arguments();


int main(int c, char **v) {
    args.setArgs(c, v);

    Filler *game;

    switch (args.algorithm) {
        case (1):
            game = new DiagonalOutwardFill(args.sqSize);
        case (2):
            game = new DiagonalInwardFill(args.sqSize);
        case (3):
            game = new NumberFill(args.sqSize);
        default:
            game = new RandomFill(args.sqSize);
    }

    game->populateGame();

    game->print();

    delete game;

    return 0;
}