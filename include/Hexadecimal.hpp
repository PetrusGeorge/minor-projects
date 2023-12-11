#ifndef HEXADECIMAL_HPP
#define HEXADECIMAL_HPP

#include "Number.hpp"

enum{A = 10, B, C, D, E, F};

class Hexadecimal : public Number{

    public:
        Hexadecimal();
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
