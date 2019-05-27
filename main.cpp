


#include <iostream>

#include "Sudoku.hpp"
#include "Filler.hpp"
#include "Arguments.hpp"


//TODO: Implement step back infrastructure to easily correct errors
//TODO: Implement a better UI
//TODO: Create command line arguments to facilitate scripts
//TODO: Ensure there is a verbosity option
//TODO: Create an export method
//TODO: Do an analysis on all algorithms implemented, perhaps create a suite to do this within the program
//TODO: would be interesting to attempt to export each step of generation into a gif or video
//TODO: DOCUMENT

Arguments args = Arguments();

void dialogue(){
    std::cout<<"Sudoku Generator "<< args.version <<
               "\n Flags: \n"
               "\t-h : print dialogue\n"
               "\t-v : verbose printing\n"
               "\t-s : size of single square of sudoku grid\n"
               "\t-a [n] : algorithm option (please see the README for options)"<<std::endl;
}



int main(int c, char * v[]) {
    std::cout << "Enter the square size of the sudoku grid: ";
    int size;
    std::cin >> size;
    std::cout << std::endl << "Generating a random fill ..." << std::endl;

    Filler *g1 = new RandomFill(size);

    g1->populateGame();


    std::cout << "Finished processing game" << std::endl;
    std::cout << "Valid game? ";
    g1->check() ? std::cout << "Yes" : std::cout << "No";
    std::cout << std::endl;

    Filler *g2 = new NumberFill(size);

    g2->populateGame();

    std::cout << "Finished processing game" << std::endl;
    std::cout << "Valid game? ";
    g2->check() ? std::cout << "Yes" : std::cout << "No";
    std::cout << std::endl;

    /*std::cout<<"Generating a correct random filling ..."<<std::endl;
    g2->populateGame();


    std::cout<<"Finished processing game"<<std::endl;
    std::cout<<"Valid game? ";
    g2->check() ? std::cout<<"Yes" : std::cout<<"No";
    std::cout<<std::endl;*/

    delete g1;
    delete g2;
    return 0;
}