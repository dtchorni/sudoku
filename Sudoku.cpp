//
// Created by dtchorni on 17/12/18.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "Sudoku.hpp"
#include "Arguments.hpp"

Sudoku::Sudoku(int s) : size(s * s), sq_size(s) {
    for (int i = 0; i < size; ++i) {
        game.emplace_back(std::vector<int *>());
        col.emplace_back(std::vector<int *>());
        row.emplace_back(std::vector<int *>());
        box.emplace_back(std::vector<int *>());
        for (int j = 0; j < size; ++j) {
            game[i].emplace_back(new int(0));
            row[i].push_back(game[i][j]);
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            col[i].push_back(game[j][i]);
        }
    }
    int b = 0;
    while (b < size) {
        int start_row = (b / sq_size) * sq_size;
        int start_col = (b % sq_size) * sq_size;
        for (int i = start_row; i < start_row + sq_size; ++i) {
            for (int j = start_col; j < start_col + sq_size; ++j) {
                box[b].push_back(game[i][j]);
            }
        }
        ++b;
    }
    for (int k = 0; k < s; ++k) {
        int first = k * pow(s, 3);
        for (int i = first; i < first + pow(s, 2); i += s) {
            topLeftCorners.push_back(i);
        }
    }
}

void Sudoku::print() {
    int lastX = getLastTile().x;
    int lastY = getLastTile().y;
    int lastVal = getLastTile().val;
    std::cout << "Last Point at X=" << lastX + 1 << ", Y=" << lastY + 1 << ", with value: " << lastVal << "\n"
              << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << "\t";
            if ((j) % sq_size == 0) std::cout << "\t";
            if (i == lastX && j == lastY) {
                printf("%c[1m", 27);  /*- turn on bold */
                printf("%c[4m", 27);  /*- turn on underline */
                std::cout << *game[i][j];
                printf("%c[0m", 27); /* turn off formatting */

            } else std::cout << *game[i][j];

        }
        std::cout << std::endl;
        if ((i + 1) % sq_size == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}


bool Sudoku::findAndPlaceNumber(int x, int y, int val) {
    assert(val <= size && val >= 1);
    int *curr = (game.at(x).at(y));
    if (*curr == 0) {
        *curr = val;
        history.emplace_back(Tile(x, y, val));
        return true;
    } else {
        return false;
    }
}

void Sudoku::findAndRemoveNumber(int x, int y, int val, int i) {
    assert(i < history.size() && i>=0);
    int *curr = game.at(x).at(y);
    *curr = 0;
    history.erase(history.begin()+i);
    if(args.verbose){
        std::cout<<"Removed "<<val<<" at x="<<x<<" and y="<<y<<std::endl;
        print();
    }

}

bool Sudoku::validateSingle(const std::vector<int *> ob) {
    std::vector<int> elements;
    for (auto e : ob) {
        if (std::find(elements.begin(), elements.end(), *e) != elements.end()) return false;
        if (*e == 0) return false;
        elements.push_back(*e);

    }
    return true;
}

bool Sudoku::validateAll() {
    for (auto c : col) {
        if (!validateSingle(c)) return false;
    }
    for (auto r : row) {
        if (!validateSingle(r)) return false;
    }
    for (auto b : box) {
        if (!validateSingle(b)) return false;
    }

    return true;
}

bool Sudoku::validatePartialSingle(const std::vector<int *> ob) {
    std::vector<int> elements;
    for (auto e : ob) {
        if (std::find(elements.begin(), elements.end(), *e) != elements.end()) return false;
        if(*e!=0) elements.push_back(*e);
    }
    return true;
}

bool Sudoku::validatePartial() {
    for (auto c : col) {
        if (!validatePartialSingle(c)) return false;
    }
    for (auto r : row) {
        if (!validatePartialSingle(r)) return false;
    }
    for (auto b : box) {
        if (!validatePartialSingle(b)) return false;
    }

    return true;
}

std::vector<int> Sudoku::generateFilledLine() {
    std::vector<int> toReturn;
    for (int i = 1; i <= size; ++i) toReturn.push_back(i);

    return toReturn;

}

bool contains(std::vector<int> *v, int check) { return ((find(v->begin(), v->end(), check)) != (v->end())); }

std::vector<int> Sudoku::availWidth(int r) {
    std::vector<int> avail = generateFilledLine();
    for (auto i : row.at(r)) {
        if (i || i != 0) avail.erase(remove(avail.begin(), avail.end(), *i), avail.end());
    }
    return avail;
}

std::vector<int> Sudoku::availHeight(int c) {
    std::vector<int> avail = generateFilledLine();
    for (auto i : col.at(c)) {
        if (i || i != 0) avail.erase(remove(avail.begin(), avail.end(), *i), avail.end());
    }
    return avail;
}

std::vector<int> Sudoku::availSquare(int s) {
    std::vector<int> avail = generateFilledLine();
    for (auto i : box.at(s)) {
        if (i || i != 0) avail.erase(remove(avail.begin(), avail.end(), *i), avail.end());
    }
    return avail;
}

std::vector<int> Sudoku::unionSet(std::vector<std::vector<int>> l) {
    std::vector<int> set = generateFilledLine();

    for (std::vector<int>::iterator a = set.begin(); a != set.end(); ++a) {
        bool unions = false;
        for (auto b : l) {
            if (contains(&b, *a)) unions = true;
            else {
                unions = false;
                break;
            }
        }
        if (!unions) {
            set.erase(a);
            --a;
        }
    }

    return set;
}

int Sudoku::findSquare(int x, int y) {
    return x / sq_size + (sq_size * (y / sq_size));
}

std::vector<int> Sudoku::getAvailAt(int x, int y) {
    assert(x <= size && y <= size);
    std::vector<std::vector<int>> avail;
    avail.push_back(availHeight(y));
    avail.push_back(availWidth(x));
    avail.push_back(availSquare(findSquare(y, x)));
    return unionSet(avail);

}



Tile Sudoku::getFirstTile() {
    assert(history.size() > 0);
    return history.at(0);
}

Tile Sudoku::getLastTile() {
    assert(history.size() > 0);
    return history.at(history.size()-1);
}

Tile Sudoku::getTileAt(int i) {
    assert(history.size() > 0 && i<history.size() && i>=0);
    return history.at(i);
}

