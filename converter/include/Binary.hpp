#ifndef BINARY_HPP
#define BINARY_HPP

#include "Number.hpp"

class Binary : public Number{

    std::vector<unsigned short> auxNumber;
    
    public:
        Binary(const std::string& number);
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();

};

#endif
