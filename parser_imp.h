#include "error.h"
#include "lexer.h"

using namespace Lexer;

namespace Parser {
    double expr(bool);
    double term(bool);
    double prim(bool);

    enum class Kind : char {
        name, number, end,
        plus = '+', 
        minus = '-', 
        mul = '*', 
        div = '/', 
        print = ';', 
        assign = '=', 
        lp = '(', 
        rp = ')'
    };

    struct Token { 
        Kind kind;
        std::string string_value;
        double number_value;
    };

}

