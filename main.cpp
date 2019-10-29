#include <iostream>
#include <sstream>
#include "lexer.h"
#include "error.h"
#include "parser_imp.h"
#include "table.h"

Lexer::Token_stream ts {cin};
void calculate() { 
    ts.get();
    if (ts.current().kind == Lexer::Kind::end) 
        break;
    if (ts.current().kind == Lexer::Kind::print) 
        continue;
    std::cout << Parser::expr(false) << '\n';
}

int main(int argc, char* argv[]) { 
    Table::table["pi"] = 3.1415926535897932385; // inser t predefined names
    Table::table["e"] = 2.7182818284590452354;
    calculate();
    return no_of_errors;
}