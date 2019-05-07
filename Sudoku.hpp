//
// Created by dtchorni on 17/12/18.
//

#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP


#include <vector>

class Sudoku {
    int size;
    int sq_size;
    std::vector<std::vector<int*>> game;


public:
    std::vector<std::vector<int*>> col;
    std::vector<std::vector<int*>> row;
    std::vector<std::vector<int*>> box;

    Sudoku(int s);
    void print();
    bool findAndPlaceNumber(int x, int y, int val); // bool number is already there
    int getSize(){ return size; }
    int getSqSize(){ return sq_size; }

    bool validateSingle(std::vector<int*> ob);

    bool validateAll();

    ~Sudoku(){
        for(auto a : game){
            for(auto b : a) delete b;
        }
    }

};

#endif //SUDOKU_SUDOKU_HPP
