#include <iostream>
#include <string>
#include "Cli.hpp"

int main(){

    Cli *cli = new Cli();

    while(true){

        try{
            cli->start();
        }catch(std::string *q){
        
            std::cout << *q << std::endl;
            delete q;
            break;
        }
    }

    delete cli;

    return 0;
}
