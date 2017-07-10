#include "Grid.h"
using namespace std;

Grid::Grid(): height(0),width(0){}

Grid::Grid(int w, int h):width(w),height(h){}

int genNum(){ return rand() % 9 + 1;}



void Grid::init(int diff){
	int num;
	for(int x=0; x<width; ++x){
		for(int y =0; y<height; ++y){
			num = genNum();
			Tile *t=new Tile(x,y,num);
			numbers.push_back(t);
		}
	}
	print();

}

void Grid::print(){
	for(int y=0; y<height; ++y){
		cout<<"\t";
		for(int x =0; x<width; ++x){
			numbers.at(2*y+x)->print();
			cout<<"  ";
		}
		cout<<"\n\n";
	}
}