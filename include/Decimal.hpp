#ifndef DECIMAL_HPP
#define DECIMAL_HPP

#include "Number.hpp"

class Decimal : public Number{

    public:
        Decimal();
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
