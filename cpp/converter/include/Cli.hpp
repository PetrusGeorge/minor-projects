#ifndef CLI_HPP
#define CLI_HPP

#include "Converter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>

class Cli{

    Converter *converter;

    unsigned short convertToType(std::string input);
    void quit();

    public:
        Cli();
        ~Cli();
        void start();
        void prompt();
        void printNumber();
};

#endif
