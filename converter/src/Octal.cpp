#include "Octal.hpp"
#include "Binary.hpp"

std::string octDigitToBinary(unsigned int octDigit) {
    switch (octDigit) {
        case 0: return "000";
        case 1: return "001";
        case 2: return "010";
        case 3: return "011";
        case 4: return "100";
        case 5: return "101";
        case 6: return "110";
        case 7: return "111";
        default: return "";
    }
}

Octal::Octal(const std::string& number){

    this->auxNumber.clear();
    this->valid = not number.empty() and number.find_first_not_of("01234567", 0) == std::string::npos;

    if(not this->valid){

        return;
    }

    for(size_t i = 0; i < number.size(); i++){

        this->auxNumber.push_back(number[i] - '0');
    }
}

std::string Octal::convertToBinary(){

    std::string output;

    for(size_t i = 0; i < this->auxNumber.size(); i++){

        output += octDigitToBinary(this->auxNumber[i]);
    }

    return output;
}

std::string Octal::convertToOctal(){

    return Number::numberToString(this->auxNumber);
}

std::string Octal::convertToDecimal(){

    std::string output;

    long unsigned sum = 0;
    for(size_t i = 0; i < this->auxNumber.size(); i++){

        sum += this->auxNumber[this->auxNumber.size() - 1 - i] * pow(8, i);
    }

    output = std::to_string(sum);

    return output;
}

std::string Octal::convertToHexadecimal(){

    Binary b = Binary(this->convertToBinary());

    return b.convertToHexadecimal();
}
