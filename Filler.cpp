//
// Created by dtchorni on 18/12/18.
//

#include <random>
#include <cassert>
#include <algorithm>
#include "Filler.hpp"

int genRand(int range) {
    assert(range > 0);
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, range - 1);
    return distr(eng);
}

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

bool EntangledFill::populateGame() {
    for (int i = 0; i < game->getSize(); ++i) {

    }
    return true;

}

bool DiagonalOutwardFill::populateGame() {
    for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {
        if (d % game->getSqSize() == 0) {
            game->findAndPlaceNumber(d, d, genRand(game->getSqSize()) + 1);
            game->print();
        }
        for (int x = d % game->getSqSize() == 0 ? d - 1 : d; x >= 0; --x) {
            std::vector<int> avail = game->getAvailAt(x, d);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(x, d,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }
        for (int y = d - 1; y >= 0; --y) {
            std::vector<int> avail = game->getAvailAt(d, y);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(d, y,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }

    }
    return true;
}

bool DiagonalInwardFill::populateGame() {
    std::vector<int> avail;
    for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {

        for (int i = 0; i < d; ++i) {
            avail = game->getAvailAt(i, d);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(i, d, avail.size() == 1 ? avail.at(0) :
                                           avail.at(genRand(avail.size())));
            game->print();
            avail = game->getAvailAt(d, i);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(d, i, avail.size() == 1 ? avail.at(0) :
                                           avail.at(genRand(avail.size())));
            game->print();

        }
        avail = game->getAvailAt(d, d);
        if (avail.empty()) return false;
        game->findAndPlaceNumber(d, d, avail.size() == 1 ? avail.at(0) :
                                       avail.at(genRand(avail.size())));
        game->print();


    }
    return true;
}

//TODO:: complete this algo..
bool DiagonalWaveFill::populateGame() {
    for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {
        if (d % game->getSqSize() == 0) {
            game->findAndPlaceNumber(d, d, genRand(game->getSqSize()) + 1);
            game->print();
        }
        for (int x = d % game->getSqSize() == 0 ? d - 1 : d; x >= 0; --x) {
            std::vector<int> avail = game->getAvailAt(x, d);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(x, d,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }
        for (int y = d - 1; y >= 0; --y) {
            std::vector<int> avail = game->getAvailAt(d, y);
            if (avail.empty()) return false;
            game->findAndPlaceNumber(d, y,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }

    }
    return true;
}


bool NumberFill::populateGame() {
    for (int i = 0; i < game->getSize(); ++i) {
        std::vector<int> avail = {};
        for (int count = 0; count < game->getSize(); ++count) {
            while (true) {
                int ind = genRand(positions.size());
                std::pair<int, int> point = positions.at(ind);
                avail = game->getAvailAt(point.first, point.second);
                if (std::find(avail.begin(), avail.end(), i + 1) != avail.end()) {
                    game->findAndPlaceNumber(point.first, point.second, i + 1);
                    positions.erase(positions.begin() + ind);
                    game->print();
                    break;
                }
            }
        }
    }
}
