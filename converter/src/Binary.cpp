#include "Binary.hpp"

Binary::Binary(const std::string& number){

    this->auxNumber.clear();
    this->valid = not number.empty() and number.find_first_not_of("01", 1) == std::string::npos;

    if(not this->valid){

        return;
    }

    for(size_t i = 0; i < number.size(); i++){

        this->auxNumber.push_back(number[i] - '0');
    }
}

std::string Binary::convertToBinary(){

    return Number::numberToString(this->auxNumber);
}

std::string Binary::convertToOctal(){

    std::string output;

    return output;
}

std::string Binary::convertToDecimal(){

    std::string output;

    return output;
}

std::string Binary::convertToHexadecimal(){

    std::string output;

    return output;
}
