//
// Created by dtchorni on 18/12/18.
//

#ifndef SUDOKU_FILLER_HPP
#define SUDOKU_FILLER_HPP


#include "Sudoku.hpp"

class Filler {
protected:
    Sudoku *game;
    int filled = 0;


public:
    Filler(int s) : game(new Sudoku(s)) {}

    Filler(Sudoku *s) : game(s) {}

    virtual bool populateGame() = 0; // bool return value: populateGame() filled the grid completely

    bool check() { return game->validateAll(); }

    ~Filler(){ delete game; }
};


class RandomFill : public Filler {

public:
    RandomFill(int s) : Filler(s) {}

    RandomFill(Sudoku *s) : Filler(s) {}

    bool populateGame() override;
};

class CorrectRandomFill : public Filler{
public:
    CorrectRandomFill(int s) : Filler(s) {}
    CorrectRandomFill(Sudoku *s) : Filler(s) {}

    bool populateGame() override;
};

#endif //SUDOKU_FILLER_HPP
