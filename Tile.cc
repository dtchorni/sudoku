#include "Tile.h"


Tile::Tile():x(0),y(0),num(0) {}

Tile::Tile(int x, int y, int num):x(x), y(y), num(num){}

void Tile::print(){ std::cout<<num; }