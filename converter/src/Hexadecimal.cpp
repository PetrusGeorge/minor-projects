#include "Hexadecimal.hpp"

short unsigned convertHexLetterToNumber(char c){

    return c - 'A' + 10;
}

Hexadecimal::Hexadecimal(const std::string& num){

    std::string number = boost::to_upper_copy(num);

    this->auxNumber.clear();
    this->valid = not number.empty() and number.find_first_not_of("0123456789ABCDEF", 0) == std::string::npos;

    if(not this->valid){

        return;
    }

    for(size_t i = 0; i < number.size(); i++){

        if(number[i] >= 'A' and number[i] <= 'F'){

            this->auxNumber.push_back(convertHexLetterToNumber(number[i]));
        }

        else{

            this->auxNumber.push_back(number[i] - '0');
        }
    }
}

std::string Hexadecimal::convertToBinary(){

    std::string output;

    return output;
}

std::string Hexadecimal::convertToOctal(){

    std::string output;

    return output;
}

std::string Hexadecimal::convertToDecimal(){

    std::string output;

    long unsigned sum = 0;
    for(size_t i = 0; i < this->auxNumber.size(); i++){

        sum += this->auxNumber[this->auxNumber.size() - 1 - i] * pow(16, i);
    }

    output = std::to_string(sum);

    return output;
}

std::string Hexadecimal::convertToHexadecimal(){

    return Number::numberToString(this->auxNumber);
}
