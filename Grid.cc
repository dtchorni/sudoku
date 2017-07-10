#include "Grid.h"
using namespace std;

Grid::Grid(): height(0),width(0){}

Grid::Grid(int w, int h):width(w),height(h){}

int genNum(int s){ return rand() % s;}


int findVal(vector<int> &a, int num){ 
	for(int i=0; i < a.size(); i++) { 
							

		if(num == a.at(i)) return i;
	}
	return -1;
}

void Grid::checkAvail(vector<int> &a, int x, int y){
	int erased =1;
	for(int i =0; i <=x; ++i){
					

		int toErase = findVal(a,numbers.at(2*i +y)->num);
		if(toErase != -1) a.erase(a.begin() + toErase);
		
	}
}



void Grid::init(int diff){
	int num;
	for(int x=0; x<width; ++x){
		for(int y =0; y<height; ++y){
			
			vector<int> avail{1,2,3,4,5,6,7,8,9};
			if(x!=0) { checkAvail(avail,x,y); }
			num = genNum(avail.size());
			cout<<"\n"<<num<<" "<<avail.size()<<endl;
			Tile *t=new Tile(x,y,avail.at(num));
			avail.erase(avail.begin() + num,avail.begin() + num);
			numbers.push_back(t);
			print();
		}
	}
	//print();

}

void Grid::print(){
	for(int i =0; i< numbers.size(); ++i){
		numbers.at(i)->print();
		cout<<"  ";
		if((i+1)%9 == 0) cout<<"\n";
	}
	cout<<"\n\n";
	/*for(int y=0; y<height; ++y){
		cout<<"\t";
		for(int x =0; x<width; ++x){
			numbers.at(2*y+x)->print();
			cout<<"  ";
		}
		cout<<"\n\n";
	}*/
}