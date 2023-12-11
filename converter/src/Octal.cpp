#include "Octal.hpp"

Octal::Octal(const std::string& number){

    this->auxNumber.clear();
    this->valid = not number.empty() and number.find_first_not_of("01234567", 1) == std::string::npos;

    if(not this->valid){

        return;
    }

    for(size_t i = 0; i < number.size(); i++){

        this->auxNumber.push_back(number[i] - '0');
    }
}

std::string Octal::convertToBinary(){

    std::string output;

    return output;
}

std::string Octal::convertToOctal(){

    return Number::numberToString(this->auxNumber);
}

std::string Octal::convertToDecimal(){

    std::string output;

    return output;
}

std::string Octal::convertToHexadecimal(){

    std::string output;

    return output;
}
