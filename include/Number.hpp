#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <string>
#include <vector>

enum{UNDEFINED, BINARY, OCTAL, DECIMAL, HEXADECIMAL};

class Number{

    std::vector<unsigned short> number;
    bool valid;

    public:
        virtual ~Number() = default;

        virtual std::string convertToBinary() = 0;
        virtual std::string convertToOctal() = 0;
        virtual std::string convertToDecimal() = 0;
        virtual std::string convertToHexadecimal() = 0;
        
        bool isValid();
};

#endif
