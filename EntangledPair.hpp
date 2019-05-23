//
// Created by dtchorni on 06/05/19.
//

#ifndef SUDOKU_ENTANGLEDPAIR_HPP
#define SUDOKU_ENTANGLEDPAIR_HPP


#include <utility>
#include <vector>

//TODO: properly implement these

struct Point {
    int val, x, y;

    Point(int v, int a, int b) : val(v), x(a), y(b) {}
};

struct Entangled {
    Point *p;
    std::vector<Entangled *> next;

    Entangled(Point *p, std::vector<Entangled *> next) : p(p), next(next) {}

    ~Entangled() {
        delete p;
        for (auto pair : next) {
            if (pair) delete pair;
        }
    }
};


#endif //SUDOKU_ENTANGLEDPAIR_HPP
