#ifndef CLI_HPP
#define CLI_HPP

#include "Converter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>

enum{UNDEFINED, BINARY, OCTAL, DECIMAL, HEXADECIMAL};
enum{A = 10, B, C, D, E, F};

class Cli{

    Converter converter;
    std::string output;
    std::pair<short unsigned, short unsigned> IOType;

    unsigned short convertToType(std::string input);
    void quit();

    public:
        Cli();
        void start();
        void prompt();
        void printNumber();
};

#endif
