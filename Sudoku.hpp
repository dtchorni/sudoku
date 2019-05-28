//
// Created by dtchorni on 17/12/18.
//

#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP


#include <vector>
#include <stack>

class Sudoku {
    int size;
    int sq_size;
    std::stack<std::pair<int,std::pair<int,int>>> history;
    std::vector<std::vector<int *>> game;

    std::vector<int> generateFilledLine();

    std::vector<int> availHeight(int);

    std::vector<int> availWidth(int);

    std::vector<int> availSquare(int);

    std::vector<int> unionSet(std::vector<std::vector<int>>);

    std::vector<int> topLeftCorners;

public:

    std::vector<std::vector<int *>> col;
    std::vector<std::vector<int *>> row;
    std::vector<std::vector<int *>> box;

    Sudoku(int s);

    void print();

    bool findAndPlaceNumber(int x, int y, int val); // bool number is already there
    int getSize() { return size; }

    int getSqSize() { return sq_size; }

    int findSquare(int, int);

    bool validateSingle(std::vector<int *> ob);

    bool validateAll();

    std::vector<int> getAvailAt(int, int);

    ~Sudoku() {
        for (auto a : game) {
            for (auto b : a) delete b;
        }
    }

};

#endif //SUDOKU_SUDOKU_HPP
