#ifndef TILE_H
#define TILE_H

#include <iostream>


struct Tile{
	int num;
	int x,y;


	Tile();
	Tile(int,int,int);
	void print();
};


#endif