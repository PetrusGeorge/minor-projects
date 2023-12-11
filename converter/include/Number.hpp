#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <string>
#include <vector>

enum{UNDEFINED, BINARY, OCTAL, DECIMAL, HEXADECIMAL};
enum{A = 10, B, C, D, E, F};

class Number{

    public:
        bool valid;
        
        virtual ~Number() = default;

        virtual std::string convertToBinary() = 0;
        virtual std::string convertToOctal() = 0;
        virtual std::string convertToDecimal() = 0;
        virtual std::string convertToHexadecimal() = 0;
        static std::string numberToString(const std::vector<unsigned short>& number); //includes Hexadecimal letters
        
        bool isValid();
};

#endif
