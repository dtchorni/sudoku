//
// Created by dtchorni on 18/12/18.
//

#include <random>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "Arguments.hpp"
#include "Filler.hpp"

int genRand(int range) {
    assert(range > 0);
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, range - 1);
    return distr(eng);
}

void RandomFill::populateGame() {
    int s = game->getSize();
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, s); // define the range
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            positions.emplace_back(std::pair<int, int>(i, j));
        }
    }
    while (true) {
        while (!positions.empty()) {
            int val = distr(eng);
            std::pair<int, int> pos = positions.at(genRand(positions.size()));
            game->findAndPlaceNumber(pos.first, pos.second, val);
            if (args.verbose) game->print();
            if (!args.ignore && args.trace && !game->validatePartial()) {
                std::vector<Tile> tr = tracer->traceBack(&val);
                for (auto tile :tr) positions.push_back(std::pair<int, int>(tile.x, tile.y));
            }
        }
        if (args.ignore) break;
        if (args.reset) {
            if (!game->validateAll()) {
                delete game;
                game = new Sudoku(args.sqSize);
            } else break;
        }
//        else if (args.trace) tracer->traceBack(t);
        else break;
    }
}

//deprecated
void CorrectRandomFill::populateGame() {
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
}
//TODO: this one
void EntangledFill::populateGame() {
    for (int i = 0; i < game->getSize(); ++i) {

    }


}

void DiagonalOutwardFill::populateGame() {
    int t = 0;
    std::vector<int> avail;
    while (true) {
        for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {
           if(game->getNumAt(d,d)==0) {
               avail = game->getAvailAt(d, d);
               if (avail.empty() && !args.ignore) return;
//               else if(avail.empty() &&)
               else if (!avail.empty())
                   game->findAndPlaceNumber(d, d,
                                            avail.size() == 1 ? avail.at(0) :
                                            avail.at(genRand(avail.size())));
               if (args.verbose) game->print();
           }
            if (d != 0) {
                for (int i = d - 1; i >= 0; --i) {
                    avail = game->getAvailAt(i, d);
                    if (avail.empty() && !args.ignore) return;
                    else if (!avail.empty())
                        game->findAndPlaceNumber(i, d,
                                                 avail.size() == 1 ? avail.at(0) :
                                                 avail.at(genRand(avail.size())));
                    if (args.verbose) game->print();

                    avail = game->getAvailAt(d, i);
                    if (avail.empty() && !args.ignore) return;
                    else if (!avail.empty())
                        game->findAndPlaceNumber(d, i,
                                                 avail.size() == 1 ? avail.at(0) :
                                                 avail.at(genRand(avail.size())));
                    if (args.verbose) game->print();


                }
            }
        }
        if (args.ignore) break;
        if (args.reset) {
            if (!game->validateAll()) {
                delete game;
                game = new Sudoku(args.sqSize);
            } else break;
        } else if (args.trace) tracer->traceBack(&t);
        else break;
    }
}

void DiagonalInwardFill::populateGame() {
    std::vector<int> avail;
    int t = 0;
    while (true) {
        for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {
            for (int i = 0; i < d; ++i) {
                if(game->getNumAt(i,d)==0) {
                    avail = game->getAvailAt(i, d);
                    if (avail.empty() && !args.ignore){
                        return;
                    }
                    else if(avail.empty() && args.trace){
                        int a=genRand(9)+1;
                        std::vector<Tile> tr = tracer->traceBack(&a);
                        for(auto t : tr){
                            d = t.x < t.y ?
                                    t.x <= d ? t.x-1 : d
                                    :
                                    t.y <= d ? t.y-1 : d;
                            break;
                        }
                    }
                    else if (!avail.empty())
                        game->findAndPlaceNumber(i, d,
                                                 avail.size() == 1 ? avail.at(0) :
                                                 avail.at(genRand(avail.size())));
                    if (args.verbose) game->print();
                }
                if(game->getNumAt(d,i)==0) {
                    avail = game->getAvailAt(d, i);
                    if (avail.empty() && !args.ignore){
                        return;
                    }
                    else if(avail.empty() && args.trace){
                        int a=genRand(9)+1;
                        std::vector<Tile> tr = tracer->traceBack(&a);
                        for(auto t : tr){
                            d = t.x < t.y ?
                                t.x <= d ? t.x-1 : d
                                          :
                                t.y <= d ? t.y-1 : d;
                            break;
                        }
                    }
                    else if (!avail.empty())
                        game->findAndPlaceNumber(d, i,
                                                 avail.size() == 1 ? avail.at(0) :
                                                 avail.at(genRand(avail.size())));
                    if (args.verbose) game->print();

                }
            }
            if(game->getNumAt(d,d)==0) {
                avail = game->getAvailAt(d, d);
                if (avail.empty() && !args.ignore){
                    return;
                }
                else if(avail.empty() && args.trace){
                    int a=genRand(9)+1;
                    std::vector<Tile> tr = tracer->traceBack(&a);
                    for(auto t : tr){
                        d = t.x < t.y ?
                            t.x <= d ? t.x-1 : d
                                      :
                            t.y <= d ? t.y-1 : d;
                        break;
                    }
                }
                else if (!avail.empty())
                    game->findAndPlaceNumber(d, d,
                                             avail.size() == 1 ? avail.at(0) :
                                             avail.at(genRand(avail.size())));
                if (args.verbose) game->print();
            }
        }

        if (args.ignore) break;
        if (args.reset) {
            if (!game->validateAll()) {
                delete game;
                game = new Sudoku(args.sqSize);
            } else break;
        }
        else break;
    }
}

//TODO:: complete this algo..
void DiagonalWaveFill::populateGame() {
    for (int d = 0; d < game->getSqSize() * game->getSqSize(); d++) {
        if (d % game->getSqSize() == 0) {
            game->findAndPlaceNumber(d, d, genRand(game->getSqSize()) + 1);
            game->print();
        }
        for (int x = d % game->getSqSize() == 0 ? d - 1 : d; x >= 0; --x) {
            std::vector<int> avail = game->getAvailAt(x, d);
//            if (avail.empty()) return false;
            game->findAndPlaceNumber(x, d,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }
        for (int y = d - 1; y >= 0; --y) {
            std::vector<int> avail = game->getAvailAt(d, y);
//            if (avail.empty()) return false;
            game->findAndPlaceNumber(d, y,
                                     avail.size() == 1 ? avail.at(0) :
                                     avail.at(genRand(avail.size())));
            game->print();
        }

    }
}

void NumberFill::populateGame() {
    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < game->getSize(); ++i) {
        while (counts.at(i) < game->getSize()) {
            std::vector<int> inds(positions.size());
            std::iota(std::begin(inds), std::end(inds), 0);
            std::shuffle(inds.begin(), inds.end(), g);

            int j = 0;
            while (j < inds.size()) {
                std::vector<int> avail = {};
                std::pair<int, int> point = positions.at(inds.at(j));
                avail = game->getAvailAt(point.first, point.second);
                if (std::find(avail.begin(), avail.end(), i + 1) != avail.end()) {
                    game->findAndPlaceNumber(point.first, point.second, i + 1);
                    positions.erase(positions.begin() + inds.at(j));
                    if (args.verbose) game->print();
                    counts.at(i)++;
                    break;
                }
                ++j;
            }
            if (j == inds.size()) {
                if (args.trace) {
                    int curr = i + 1;
                    std::vector<Tile> tr = tracer->traceBack(&curr);
                    for (auto t : tr) {
                        positions.push_back(std::pair<int, int>(t.x, t.y));
                        counts.at(t.val - 1)--;
                        if ((t.val - 1) < i) i = t.val - 1;
                    }
                } else if (args.ignore) break;
                else if (args.reset) {
                    if (!game->validateAll()) {
                        delete game;
                        game = new Sudoku(args.sqSize);
                    } else break;
                } else break;
            }

        }
    }
}
