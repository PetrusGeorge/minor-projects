#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include "Number.hpp"
#include "Binary.hpp"
#include "Octal.hpp"
#include "Decimal.hpp"
#include "Hexadecimal.hpp"
#include <string>

class Converter{

    Number *toBeConverted;
    short unsigned outputType;

    public:
        Converter();
        ~Converter();
        Converter(const std::string& number, short unsigned inputType, short unsigned outputType);
        bool checkIfNumberIsValid();
        std::string converte();
};

#endif
