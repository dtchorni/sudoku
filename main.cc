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
    cout<<"Size of Grid :";
    int diff;
    cin>>diff;
    Grid game(diff);
    game.init(diff);



}