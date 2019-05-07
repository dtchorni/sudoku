//
// Created by dtchorni on 17/12/18.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "Sudoku.hpp"

Sudoku::Sudoku(int s):size(s*s),sq_size(s) {
    for(int i=0; i<size; ++i){
        game.emplace_back(std::vector<int*>());
        col.emplace_back(std::vector<int*>());
        row.emplace_back(std::vector<int*>());
        box.emplace_back(std::vector<int*>());
        for(int j =0; j < size;++j){
            game[i].emplace_back(new int(0));
            row[i].push_back(game[i][j]);
        }
    }
    for(int i=0; i<size;++i){
        for(int j=0;j <size;++j){
            col[i].push_back(game[j][i]);
        }
    }
    int b =0;
    while(b<size){
        int start_row = b/sq_size;
        int start_col = (b%sq_size)*sq_size;
        for(int i = start_row; i < start_row+sq_size; ++i){
            for(int j= start_col; j < start_col+sq_size; ++j){
                box[b].push_back(game[i][j]);
            }
        }
        ++b;
    }
}

void Sudoku::print() {
    for(int i =0; i < size; ++i){
        for(int j =0; j<size;++j) {
            std::cout << "\t";
            if((j)%sq_size==0) std::cout<<"\t";
            std::cout<< *game[i][j];

        }
        std::cout<<std::endl;
        if((i+1)%sq_size==0) std::cout<<std::endl;
    }
    std::cout<<std::endl;
}


bool Sudoku::findAndPlaceNumber(int x, int y, int val) {
    assert(val<=size && val>=1);
    int *curr = (game.at(x).at(y));
    if(*curr==0){
        *curr=val;
        return true;
    }else{
        return false;
    }
}

bool Sudoku::validateSingle(const std::vector<int*> ob) {
    std::vector<int> elements;
    for(auto e : ob){
        if(std::find(elements.begin(),elements.end(), *e)!=elements.end()) return false;
        if(*e==0) return false;
        elements.push_back(*e);

    }
    return true;
}

bool Sudoku::validateAll() {
    for(auto c : col){
        if(!validateSingle(c)) return false;
    }for(auto r : row){
        if(!validateSingle(r)) return false;
    }for(auto b : box){
        if(!validateSingle(b)) return false;
    }

    return true;
}