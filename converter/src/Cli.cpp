#include "Cli.hpp"

Cli::Cli(){

    this->converter = NULL;
}

Cli::~Cli(){

    if(converter != NULL){
        delete converter;
    }
}

void Cli::start(){

    this->prompt();
    this->printNumber();
}

void Cli::prompt(){

    std::string input;
    std::pair<short unsigned, short unsigned> IOType;

    while(true){
        std::cout << "Enter the input type, B = Binary, O = Octal, D = Decimal, H = Hexadecimal, Q = quit program" << std::endl;
        std::cin >> input;
        std::cin.ignore();

        IOType.first = this->convertToType(input);

        if(IOType.first != UNDEFINED){

            break;
        }

        std::cout << "Invalid value, try again" << std::endl;
    }

    while(true){
        std::cout << "Enter the output type, B = Binary, O = Octal, D = Decimal, H = Hexadecimal, Q = quit program" << std::endl;
        std::cin >> input;
        std::cin.ignore();

        IOType.second = this->convertToType(input);

        if(IOType.second != UNDEFINED){

            break;
        }

        std::cout << "Invalid value, try again" << std::endl;
    }

    while(true){
        std::cout << "Enter a value (Q = Sair do programa)" << std::endl;
        std::cin >> input;
        std::cin.ignore();

        this->convertToType(input); //checks if it has to quit
        
        this->converter = new Converter(input, IOType.first, IOType.second);

        if(converter->checkIfNumberIsValid()){

            break;
        }

        delete converter;
        converter = NULL;

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

void Cli::printNumber(){

    std::cout << "The corresponding number is: ";
    std::cout << this->converter->convert() << std::endl;
}

void Cli::quit(){

    std::string *mensage = new std::string("O programa terminou");

    throw mensage;
}
