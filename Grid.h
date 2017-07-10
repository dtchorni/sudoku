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
	std::vector<Tile*> numbers;

public:
	Grid();
	Grid(int,int);
	void init(int diff);
	void checkAvail(std::vector<int> &, int , int );

	void print();
	

};

#endif