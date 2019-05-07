


#include <iostream>

#include "Sudoku.hpp"
#include "Filler.hpp"

int main(){
    std::cout<<"Enter the square size of the sudoku grid: ";
    int size;
    std::cin>>size;
    std::cout<<std::endl<<"Generating a random fill ..."<<std::endl;

    Filler *g1 = new RandomFill(size);

    g1->populateGame();


    std::cout<<"Finished processing game"<<std::endl;
    std::cout<<"Valid game? ";
    g1->check() ? std::cout<<"Yes" : std::cout<<"No";
    std::cout<<std::endl;

    Filler *g2 = new CorrectRandomFill(size);

    std::cout<<"Generating a correct random filling ..."<<std::endl;
    g2->populateGame();


    std::cout<<"Finished processing game"<<std::endl;
    std::cout<<"Valid game? ";
    g2->check() ? std::cout<<"Yes" : std::cout<<"No";
    std::cout<<std::endl;

    delete g1;
    delete g2;
    return 0;
}