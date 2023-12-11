#include "Converter.hpp"

Converter::Converter(){
    
    this->toBeConverted = NULL;
    this->outputType = UNDEFINED;
}

Converter::~Converter(){

    if(toBeConverted != NULL){
        delete toBeConverted;
    }
}

Converter::Converter(const std::string& number, short unsigned inputType, short unsigned outputType){

    this->outputType = outputType;

    switch(inputType){

        case BINARY:
            toBeConverted = new Binary();
    }
}

bool Converter::checkIfNumberIsValid(){

    return toBeConverted->isValid();
}

std::string Converter::converte(){

    std::string output;

    return output;
}
