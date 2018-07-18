#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tile.h"


class Grid{
	int height, width;
	int square;
    std::vector<Tile*> *numbers;

public:
	Grid();
	explicit Grid(int);
	void init(int diff);

    void clearSomething(int x, int y);
    void clearSquare(int s);
	std::vector<int> topLeftCorners;

	std::vector<int> generateFilledLine();

	std::vector<int> availHeight(int, int);
	std::vector<int> availWidth(int, int);
	std::vector<int> availSquare(int, int);

	std::vector<int> unionSet(std::vector<std::vector<int>> *);

	void print();
	

};

#endif