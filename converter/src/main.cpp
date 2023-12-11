#include <iostream>
#include <string>
#include "Cli.hpp"

int main(){

    Cli *cli = new Cli();

    try{
        cli->start();
    }catch(std::string *e){
    
        std::cout << *e << std::endl;
        delete e;
    }

    delete cli;

    return 0;
}
