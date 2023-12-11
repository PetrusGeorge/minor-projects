#ifndef DECIMAL_HPP
#define DECIMAL_HPP

#include "Number.hpp"

class Decimal : public Number{
    
   std::vector<unsigned short> auxNumber;

    public:
        Decimal(const std::string& number);
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
