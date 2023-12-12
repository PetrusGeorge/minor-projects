#include "Hexadecimal.hpp"
#include "Binary.hpp"

std::string hexDigitToBinary(unsigned short hexDigit) {
    switch (hexDigit) {
        case 0: return "0000";
        case 1: return "0001";
        case 2: return "0010";
        case 3: return "0011";
        case 4: return "0100";
        case 5: return "0101";
        case 6: return "0110";
        case 7: return "0111";
        case 8: return "1000";
        case 9: return "1001";
        case A: return "1010";
        case B: return "1011";
        case C: return "1100";
        case D: return "1101";
        case E: return "1110";
        case F: return "1111";
        default: return "";
    }
}

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

    for(size_t i = 0; i < this->auxNumber.size(); i++){

        output += hexDigitToBinary(this->auxNumber[i]);
    }

    return output;
}

std::string Hexadecimal::convertToOctal(){

    Binary b = Binary(this->convertToBinary());

    return b.convertToOctal();;
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
