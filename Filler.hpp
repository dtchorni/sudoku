//
// Created by dtchorni on 18/12/18.
//

#ifndef SUDOKU_FILLER_HPP
#define SUDOKU_FILLER_HPP


#include "EntangledPair.hpp"
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

    virtual bool populateGame() override;
};

class EntangledFill : public Filler {
    std::vector<Entangled *> pairs;

public:
    EntangledFill(int s) : Filler(s) {}

    EntangledFill(Sudoku *s) : Filler(s) {}

    virtual bool populateGame() override;

};

class CorrectRandomFill : public Filler{
public:
    CorrectRandomFill(int s) : Filler(s) {}
    CorrectRandomFill(Sudoku *s) : Filler(s) {}

    bool populateGame() override;
};

class DiagonalFill : public Filler {
public:
    DiagonalFill(int s) : Filler(s) {}
    DiagonalFill(Sudoku *s) : Filler(s) {}

    bool populateGame() override;
};
};

#endif //SUDOKU_FILLER_HPP
