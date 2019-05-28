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

    virtual void populateGame() = 0; // void return value: populateGame() filled the grid completely

    void print(){ game->print(); }

    ~Filler() { delete game; }
};

//Algorithm 0: randomly places numbers on grid
class RandomFill : public Filler {

public:
    RandomFill(int s) : Filler(s) {}

    RandomFill(Sudoku *s) : Filler(s) {}

    virtual void populateGame() override;
};


//Deprecated with reset flag
class CorrectRandomFill : public Filler {
public:
    CorrectRandomFill(int s) : Filler(s) {}

    CorrectRandomFill(Sudoku *s) : Filler(s) {}

    void populateGame() override;
};

//Algorithm 1:
class DiagonalOutwardFill : public Filler {
public:
    DiagonalOutwardFill(int s) : Filler(s) {}

    DiagonalOutwardFill(Sudoku *s) : Filler(s) {}

    void populateGame() override;
};

//Algorithm 2:
class DiagonalInwardFill : public Filler {
public:
    DiagonalInwardFill(int s) : Filler(s) {}

    DiagonalInwardFill(Sudoku *s) : Filler(s) {}

    void populateGame() override;
};

//Algorithm 3:
class NumberFill : public Filler {
    std::vector<std::pair<int, int>> positions;
public:
    NumberFill(int s) : Filler(s) {
        for (int x = 0; x < game->getSize(); ++x) {
            for (int y = 0; y < game->getSize(); ++y) {
                positions.push_back(std::pair<int, int>(x, y));
            }
        }
    }

    NumberFill(Sudoku *s) : Filler(s) {}

    void populateGame() override;
};

//TODO: implement this
class EntangledFill : public Filler {
    std::vector<Entangled *> pairs;

public:
    EntangledFill(int s) : Filler(s) {}

    EntangledFill(Sudoku *s) : Filler(s) {}

    virtual void populateGame() override;

};

//TODO: implement this vvvv
class DiagonalWaveFill : public Filler {
public:
    DiagonalWaveFill(int s) : Filler(s) {}

    DiagonalWaveFill(Sudoku *s) : Filler(s) {}

    void populateGame() override;
};

#endif //SUDOKU_FILLER_HPP
