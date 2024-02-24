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
            this->toBeConverted = new Binary(number);
            break;

        case OCTAL:
            this->toBeConverted = new Octal(number);
            break;

        case DECIMAL:
            this->toBeConverted = new Decimal(number);
            break;

        case HEXADECIMAL:
            this->toBeConverted = new Hexadecimal(number);
            break;
    }
}

bool Converter::checkIfNumberIsValid(){

    if(toBeConverted != NULL){
        return toBeConverted->isValid();
    }

    return false;
}

std::string Converter::convert(){

    std::string output;

    switch(this->outputType){

        case BINARY:
            output = toBeConverted->convertToBinary();
            break;

        case OCTAL:
            output = toBeConverted->convertToOctal();
            break;

        case DECIMAL:
            output = toBeConverted->convertToDecimal();
            break;

        case HEXADECIMAL:
            output = toBeConverted->convertToHexadecimal();
            break;

    }

    return output;
}
