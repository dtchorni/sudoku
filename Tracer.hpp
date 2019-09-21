//
// Created by dtchorni on 30/06/19.
//

#ifndef SUDOKU_TRACER_HPP
#define SUDOKU_TRACER_HPP


#include "Sudoku.hpp"

class Tracer {
protected:
    Sudoku *game;

public:

    Tracer(Sudoku *g) : game(g) {}

    virtual std::vector<Tile> traceBack(int *) = 0;
};

class FIFOtrace : public Tracer {
public:

    FIFOtrace(Sudoku *g) : Tracer(g) {}

    std::vector<Tile> traceBack(int *) override;
};

class LIFOtrace : public Tracer {
public:
    LIFOtrace(Sudoku *g) : Tracer(g) {}

    std::vector<Tile> traceBack(int *) override;
};

class MatchNumberTrace : public Tracer{
public:
    MatchNumberTrace(Sudoku *g) : Tracer(g) {}
    std::vector<Tile> traceBack(int * ) override;
};


#endif //SUDOKU_TRACER_HPP
