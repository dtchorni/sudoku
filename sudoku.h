#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku{
	int diff;
	std::vector<Tile*> game;

public:
	Sudoku();
	Sudoku(int, std::vector<Tile*>);
	
};


#endif