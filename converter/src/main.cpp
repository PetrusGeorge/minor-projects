#include <iostream>
#include <string>
#include "Cli.hpp"

int main(){

    Cli cli;

    try{
        cli.start();
    }catch(std::string *e){
    
        std::cout << *e << std::endl;
        delete e;
    }

    return 0;
}
