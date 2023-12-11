#include "Decimal.hpp"

Decimal::Decimal(const std::string& number){

    this->auxNumber.clear();
    this->valid = not number.empty() and number.find_first_not_of("0123456789", 1) == std::string::npos;

    if(not this->valid){

        return;
    }

    for(size_t i = 0; i < number.size(); i++){

        this->auxNumber.push_back(number[i] - '0');
    }
}

std::string Decimal::convertToBinary(){

    std::string output;

    return output;
}

std::string Decimal::convertToOctal(){

    std::string output;

    return output;
}

std::string Decimal::convertToDecimal(){

    return Number::numberToString(this->auxNumber);
}

std::string Decimal::convertToHexadecimal(){

    std::string output;

    return output;
}
