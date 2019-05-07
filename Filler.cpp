//
// Created by dtchorni on 18/12/18.
//

#include <random>
#include "Filler.hpp"


bool RandomFill::populateGame() {
    int s = game->getSize();
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, s); // define the range
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            game->findAndPlaceNumber(i, j, distr(eng));
        }
        game->print();
    }
    return true;
}

bool CorrectRandomFill::populateGame() {
    int s = game->getSize();
    int sq = game->getSqSize();
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, s); // define the range
    while (!game->validateAll()) {
        delete game;
        game = new Sudoku(sq);
        for (int i = 0; i < s; ++i) {
            for (int j = 0; j < s; ++j) {
                game->findAndPlaceNumber(i, j, distr(eng));
            }
        }
        game->print();
    }
    return true;
}