#include "Binary.hpp"
#include <iostream>

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

    for(auto it = this->auxNumber.rbegin(); it < this->auxNumber.rend();){

        std::vector<unsigned short> aux;
        for(int i = 0; i < 3; i++){

            aux.push_back(*it);
            it++;
            if(it >= this->auxNumber.rend()){
            
                break;
            }
        }
        std::reverse(aux.begin(), aux.end());

        output = std::to_string(Number::binToDec(aux)) + output;
    }

    return output;
}

std::string Binary::convertToDecimal(){

    std::string output;
    output = std::to_string(Number::binToDec(this->auxNumber));

    return output;
}

std::string Binary::convertToHexadecimal(){

    std::string output;

    for(auto it = this->auxNumber.rbegin(); it < this->auxNumber.rend();){

        std::vector<unsigned short> aux;
        for(int i = 0; i < 4; i++){

            aux.push_back(*it);
            it++;
            if(it >= this->auxNumber.rend()){
            
                break;
            }
        }
        std::reverse(aux.begin(), aux.end());

        output = Number::numberToString(std::vector<unsigned short>(1,Number::binToDec(aux))) + output;
    }

    return output;
}
