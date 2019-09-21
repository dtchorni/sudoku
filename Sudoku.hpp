//
// Created by dtchorni on 17/12/18.
//

#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP


#include <vector>
#include <stack>

struct Tile{
    int x;
    int y;
    int val;
    Tile(int a,int b, int c) : x(a), y(b) , val(c) {}
};

class Sudoku {
    int size;
    int sq_size;
    std::vector<Tile> history;
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

    void findAndRemoveNumber(int x, int y, int val, int i);

    int getSize() { return size; }

    int getSqSize() { return sq_size; }

    int findSquare(int, int);

    bool validateSingle(std::vector<int *> ob);

    bool validateAll();

    bool validatePartial();

    bool validatePartialSingle(std::vector<int *> obj);

    std::vector<int> getAvailAt(int, int);

    int getNumAt(int x, int y) { return *(game.at(x).at(y)); }

    ~Sudoku() {
        for (auto a : game) {
            for (auto b : a) delete b;
        }
    }

    Tile getLastTile();
    Tile getFirstTile();
    unsigned int totalTiles() { return history.size(); }
    Tile getTileAt(int);

};

#endif //SUDOKU_SUDOKU_HPP
