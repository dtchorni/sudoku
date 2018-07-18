#include <cmath>
#include "Grid.h"
#include <algorithm>
#include <cassert>

using namespace std;


Grid::Grid(): height(0),width(0){}



Grid::Grid(int s):width(s*s),height(s*s){
    square =s;
    for(int k =0; k<s; ++k){
        int first = k*pow(s,3);
        for(int i = first; i < first+ pow(s,2); i+=s){
            topLeftCorners.push_back(i);
        }
    }
	numbers = new vector<Tile *>();
	for(int i=0; i <s*s*s*s; ++i) {
		numbers->push_back(new Tile(0, 0, 0));
	}


}

int genNum(int s){ return rand() % s;}


int findVal(vector<int> &a, int num){ 
	for(int i=0; i < a.size(); i++) { 
							

		if(num == a.at(i)) return i;
	}
	return -1;
}



vector<int> Grid::generateFilledLine() {
	vector<int> toReturn;
	for(int i =1; i <= width; ++i) toReturn.push_back(i);

	return toReturn;

}

bool contains(vector<int> *v, int check){ return ((find(v->begin(), v->end(), check)) != (v->end())) ;}

vector<int> Grid::availWidth(int x, int y) {
    //2cout<<"width @: "<<x<<" "<<y<<": ";
	vector<int> curr = generateFilledLine();

	for(int i=y*height; i < ((y*height)+width); ++i){
        //cout<<numbers->at(i)->num<<" ";
		if(numbers->at(i)->num!=0) {
			curr.erase(remove(curr.begin(), curr.end(), numbers->at(i)->num), curr.end());
		}
	}
    //cout<<endl;
	return curr;
}

vector<int> Grid::availHeight(int x, int y) {
    //cout<<"height @: "<<x<<" "<<y<<": ";
	vector<int> curr = generateFilledLine();
	for(int i=x; i <= ((height*(height-1))+x); (i+=height)){
        //cout<<numbers->at(i)->num<<" ";
		if(numbers->at(i)->num!=0) {
			curr.erase(remove(curr.begin(), curr.end(), numbers->at(i)->num), curr.end());
		}
	}

    //cout<<endl;
	return curr;
}

vector<int> Grid::availSquare(int x, int y) {
    int curr_square = x/(square) + (square*(y/(square)));
    vector<int> sq = generateFilledLine();
	//cout<<"square @: "<<curr_square<<"("<<x<<" "<<y<<"): ";
    int currTopLeft = topLeftCorners.at(curr_square);

    for(int i = currTopLeft; i<(currTopLeft+(square*height)); i+=height){
        for(int j=i; j<(i+square); ++j){
            //cout<<numbers->at(j)->num<<" ";
            if(numbers->at(j)->num!=0){
                sq.erase(remove(sq.begin(), sq.end(), numbers->at(j)->num),sq.end());
            }
        }
    }
    //cout<<endl;
    return sq;

}

vector<int> Grid::unionSet(vector<vector<int>> *l) {
    vector<int> set = generateFilledLine();

	for( vector<int>::iterator a = set.begin(); a!=set.end(); ++a ){
		bool unions = false;
		for(auto b : *l){
			if(contains(&b,*a)) unions=true;
			else{
				unions=false;
				break;
			}
		}
		if(!unions){
			set.erase(a);
			--a;
		}
	}

    return set;
}


void Grid::clearSquare(int s) {
   // cout<<s<<endl;
    int currTopLeft = topLeftCorners.at(s);
    for(int i = currTopLeft; i<(currTopLeft+(square*height)); i+=height){
        for(int j=i; j<(i+square); ++j){
            numbers->at(j)->set(0,0,0);
        }
    }
}

void Grid::clearSomething(int x, int y) {
    int smt = genNum(3);
    switch(smt){
        case 0 ://clear row
            for(int i = x; i>=0; --i){
                numbers->at((height*y)+i)->set(0,0,0);
            }
            break;
        case 1: //clear column
            for(int i = (height*y)+x; i>=x; i-=height){
                numbers->at(i)->set(0,0,0);
            }
            break;
        default: //clear some square
            int curr_square = x/(square) + (square*(y/(square)));
            int r2 = genNum(3);
            switch(r2){
                case 0: //clear box to the left
                    if(curr_square%square!=0) curr_square--;
                    break;
                case 1: //clear box above
                    if(curr_square>square) curr_square-=square;
                    break;
                default://clear current box
                    break;
            }
            clearSquare(curr_square);
            break;
    }

}

    void Grid::init(int diff){
        int num;

	for(int y=0; y<width; ++y){
		for(int x =0; x<height; ++x){
            if(numbers->at((height*y)+x)->num==0) {
                vector<int> avail;
                while (true) {
                    vector<vector<int>> allAvail;
                    allAvail.push_back(availHeight(x, y));
                    allAvail.push_back(availWidth(x, y));
                    allAvail.push_back(availSquare(x, y));
                    avail = unionSet(&allAvail);
                    if (avail.empty()) {
                        clearSomething(x,y);
                        //cout << "FUCK" << endl;
                        //print();
                        x = 0;
                        y = 0;
                    } else break;
                }
                //vector<int> avail = generateFilledLine();


                num = genNum(avail.size());
                //cout<<"\n"<<num<<" "<<avail.size()<<endl;
                Tile *t = new Tile(x, y, avail.at(num));
                avail.erase(avail.begin() + num, avail.begin() + num);
                //cout << "WHERE: " << (height * x) + y << endl;
                numbers->at((height * y) + x)->set(x, y, avail.at(num));
                //print();
            }
		}
	}
	print();

}

void Grid::print(){
    int lineLength = width+width-1+(2*(square)-1)-1;
	for(int i =0; i < lineLength; ++i) cout<<"_";
	cout<<endl;
	for(int i =0; i< numbers->size(); ++i){
		numbers->at(i)->print();
		cout<<" ";
		if((i+1)%(width) == 0) {
			cout<<"\n";
            if((i+1)%(square*square*square ) == 0) {
				for(int i =0; i < lineLength; ++i) cout<<"_";
				cout<<endl;
			}
		}else if((i+1)%(square)==0) cout<<"| ";

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