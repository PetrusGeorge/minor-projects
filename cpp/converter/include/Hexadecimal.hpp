#ifndef HEXADECIMAL_HPP
#define HEXADECIMAL_HPP

#include "Number.hpp"
#include <boost/algorithm/string.hpp>

class Hexadecimal : public Number{

    std::vector<unsigned short> auxNumber;

    public:
        Hexadecimal(const std::string& number);
        std::string convertToBinary();
        std::string convertToOctal();
        std::string convertToDecimal();
        std::string convertToHexadecimal();
};

#endif
