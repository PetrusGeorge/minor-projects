#include "Cli.hpp"

Cli::Cli(){

    this->converter = Converter();
    this->output.clear();
    this->IOType = std::make_pair(UNDEFINED, UNDEFINED);

}

void Cli::start(){

    this->prompt();
}

void Cli::prompt(){

    std::string input;


    while(true){
        std::cout << "Enter the input type, B = Binary, O = Octal, D = Decimal, H = Hexadecimal, Q = quit program" << std::endl;
        std::cin >> input;
        std::cin.ignore();

        this->IOType.first = this->convertToType(input);

        if(IOType.first != UNDEFINED){

            break;
        }

        std::cout << "Invalid value, try again" << std::endl;
    }

    while(true){
        std::cout << "Enter a value (Q = Sair do programa)" << std::endl;
        std::cin >> input;
        std::cin.ignore();


        std::cout << "Invalid value, try again" << std::endl;
    }

    while(true){
        std::cout << "Enter the output type, B = Binary, O = Octal, D = Decimal, H = Hexadecimal, Q = quit program" << std::endl;
        std::cin >> input;
        std::cin.ignore();

        this->IOType.second = this->convertToType(input);

        if(IOType.second != UNDEFINED){

            break;
        }

        std::cout << "Invalid value, try again" << std::endl;
    }
}

short unsigned Cli::convertToType(std::string input){

    boost::to_upper(input);

    if(input == "Q"){
         
        quit();
    }

    if(input == "B"){

        return BINARY;
    }

    if(input == "O"){

        return OCTAL;
    }

    if(input == "D"){

        return DECIMAL;
    }

    if(input == "H"){

        return HEXADECIMAL;
    }

    return UNDEFINED;
    
}

void Cli::quit(){

    std::string *mensage = new std::string("O programa terminou");

    throw mensage;
}
