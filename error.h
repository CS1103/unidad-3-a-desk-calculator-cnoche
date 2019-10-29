#ifndef CALCULADORA_ERROR_H
#define CALCULADORA_ERROR_H
#include<iostream>
#include<string>

int no_of_errors;
double error(const std::string& s) { 
    ++no_of_errors;
    std::cerr << "Error: " << s << '\n';
    return 1;
}

#endif