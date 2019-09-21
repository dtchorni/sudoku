


#include <iostream>

#include "Sudoku.hpp"
#include "Filler.hpp"
#include "Arguments.hpp"
#include "Tracer.hpp"


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

    Sudoku *game = new Sudoku(args.sqSize);

    Tracer *tracer;

    switch (args.tracer) {
        case (1) :
            tracer = new LIFOtrace(game);
            break;
        case(2):
            tracer = new MatchNumberTrace(game);
            break;
        default:
            tracer = new FIFOtrace(game);
    }

    Filler *filler;

    switch (args.algorithm) {
        case (1):
            filler = new DiagonalOutwardFill(game, tracer);
            break;
        case (2):
            filler = new DiagonalInwardFill(game, tracer);
            break;
        case (3):
            filler = new NumberFill(game, tracer);
            break;
        default:
            filler = new RandomFill(game, tracer);
    }

    filler->populateGame();

    game->print();

    delete game;

    return 0;
}