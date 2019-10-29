#include<iostream>
#include<sstream>
#include"error.h"

namespace Error {
    int no_of_errors;
    double error(const std::string& s) { 
        no_of_errors++;
        std::cerr << "error: " << s << '\n';
        return 1;
    }
}