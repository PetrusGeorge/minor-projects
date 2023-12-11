#ifndef BINARY_HPP
#define BINARY_HPP

#include "Number.hpp"

class Binary : public Number{

    public:
        Binary();
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();

};

#endif
