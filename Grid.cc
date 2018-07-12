#include <cmath>
#include "Grid.h"
#include <algorithm>
using namespace std;

Grid::Grid(): height(0),width(0){}

Grid::Grid(int s):width(s*s),height(s*s){}

int genNum(int s){ return rand() % s;}


int findVal(vector<int> &a, int num){ 
	for(int i=0; i < a.size(); i++) { 
							

		if(num == a.at(i)) return i;
	}
	return -1;
}



vector<int> Grid::generateFilledLine() {
	vector<int> toReturn;
	for(int i =0; i < width; ++i) toReturn.push_back(i);

	return toReturn;

}

bool contains(vector<int> *v, int check){ return ((find(v->begin(), v->end(), check)) != (v->end())) ;}

vector<int> Grid::availWidth(int x, int y) {
	vector<int> curr = generateFilledLine();
	for(int i=y*height; i < ((y*height)+x); ++i){
		curr.erase(remove( curr.begin(), curr.end(), numbers.at(i)->num ), curr.end() );
	}
	return curr;
}

vector<int> Grid::availHeight(int x, int y) {
	vector<int> curr = generateFilledLine();
	for(int i=x; i < ((y*height)+x); (i+=height)){
		curr.erase(remove( curr.begin(), curr.end(), numbers.at(i)->num ), curr.end() );
	}
	return curr;
}

vector<int> Grid::availSquare(int, int) {

}

vector<int> Grid::unionSet(std::vector<std::vector<int>>) {

}

void Grid::init(int diff){
	int num;
	for(int x=0; x<width; ++x){
		vector<int> avail{1,2,3,4,5,6,7,8,9};

		for(int y =0; y<height; ++y){
			
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
	for(int i =0; i < (width*sqrt(width) - sqrt(width)); ++i) cout<<"_";
	cout<<endl;
	for(int i =0; i< numbers.size(); ++i){
		numbers.at(i)->print();
		cout<<" ";
		if((i+1)%(width) == 0) {
			cout<<"\n";
			int square = (int) ((width*sqrt(width)));
			if((i+1)%square  == 0) {
				for(int i =0; i < (width*sqrt(width) - sqrt(width)); ++i) cout<<"_";
				cout<<endl;
			}
		}else if((i+1)%((int)sqrt(width))==0) cout<<" | ";

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