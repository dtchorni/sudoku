#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grid.h"
using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    Grid game(2);
    cout<<"Trace back by how many steps? :";
    int diff;
    cin>>diff;
    game.init(diff);



}