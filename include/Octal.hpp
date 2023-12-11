#ifndef OCTAL_HPP
#define OCTAL_HPP

#include "Number.hpp"

class Octal : public Number{

    public:
        Octal();
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
