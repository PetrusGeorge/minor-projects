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
