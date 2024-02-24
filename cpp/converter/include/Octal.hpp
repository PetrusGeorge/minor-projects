#ifndef OCTAL_HPP
#define OCTAL_HPP

#include "Number.hpp"

class Octal : public Number{

    std::vector<unsigned short> auxNumber;

    public:
        Octal(const std::string& number);
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
