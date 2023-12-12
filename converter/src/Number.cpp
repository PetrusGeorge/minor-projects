#include "Number.hpp"

bool Number::isValid(){

    return this->valid;
}

std::string Number::numberToString(const std::vector<unsigned short>& number){

    std::string output;

    for(size_t i = 0; i < number.size(); i++){

        output += "0123456789ABCDEF"[number[i]];
    }

    return output;
}

unsigned long Number::binToDec(const std::vector<unsigned short>& bin){

    long unsigned sum = 0;
    for(size_t i = 0; i < bin.size(); i++){

        sum += bin[bin.size() - 1 - i] * pow(2, i);
    }

    return sum;
}
