//
// Created by dtchorni on 18/12/18.
//

#ifndef SUDOKU_FILLER_HPP
#define SUDOKU_FILLER_HPP


#include "EntangledPair.hpp"
#include "Sudoku.hpp"
#include "Tracer.hpp"


class Filler {
protected:
    Sudoku *game;
    int filled = 0;
    Tracer *tracer;
    
public:
//    Filler(int s, Tracer *t) : game(new Sudoku(s)), tracer(t) {}

    Filler(Sudoku *s, Tracer *t) : game(s), tracer(t) {}

    virtual void populateGame() = 0; // void return value: populateGame() filled the grid completely

    void print(){ game->print(); }

    ~Filler() { delete game; }
};

//Algorithm 0: randomly places numbers on grid
class RandomFill : public Filler {

public:

    RandomFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    virtual void populateGame() override;
};


//Deprecated with reset flag
class CorrectRandomFill : public Filler {
public:

    CorrectRandomFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    void populateGame() override;
};

//Algorithm 1:
class DiagonalOutwardFill : public Filler {
public:

    DiagonalOutwardFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    void populateGame() override;
};

//Algorithm 2:
class DiagonalInwardFill : public Filler {
public:

    DiagonalInwardFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    void populateGame() override;
};

//Algorithm 3:
class NumberFill : public Filler {
    std::vector<std::pair<int, int>> positions;
    std::vector<int> counts;
public:

    NumberFill(Sudoku *s, Tracer *t) : Filler(s,t) {
        for (int x = 0; x < game->getSize(); ++x) {
            for (int y = 0; y < game->getSize(); ++y) {
                positions.push_back(std::pair<int, int>(x, y));
            }
        }
        counts = std::vector<int>(game->getSize());
    }

    void populateGame() override;
};

//TODO: implement this
class EntangledFill : public Filler {
    std::vector<Entangled *> pairs;

public:

    EntangledFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    virtual void populateGame() override;

};

//TODO: implement this vvvv
class DiagonalWaveFill : public Filler {
public:

    DiagonalWaveFill(Sudoku *s, Tracer *t) : Filler(s,t) {}

    void populateGame() override;
};




#endif //SUDOKU_FILLER_HPP
