#include "lexer.h"
#include "parser_imp.h"
#include "table.h"
#include "error.h"
#include <iostream>


namespace Parser{
    Lexer::Token_stream ts;
    double Parser::prim(bool get) {
        if (get) ts.get(); // read next token
            switch (ts.current().kind) {
            case Lexer::Kind::number: { // floating-point constant
                double v = ts.current().number_value;
                ts.get();
                return v;

            }
            case Lexer::Kind::name: {
                double& v = Table::table[ts.current().string_value]; // find the corresponding
                if (ts.get().kind == Lexer::Kind::assign) 
                    v = expr(true); // ’=’ seen: assignment
                    return v;
            }
            case Lexer::Kind::minus: // suma y minus
                return -prim(true);
            case Lexer::Kind::lp: {
                auto e = expr(true);
                if (ts.current().kind != Lexer::Kind::rp) 
                    return error("')' expected");
                    ts.get(); // eat ’)’
                    return e;
            }
        default:
            return error("primar y expected");
        }
    }


    double Parser::term(bool get) { //mult y div
        double left = prim(get);
        for (;;) {
            switch (ts.current().kind) {
            case Lexer::Kind::mul:
                left *= prim(true);
                break;
            case Lexer::Kind::div:
                if (auto d = prim(true)) {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
            }
        }
    }
    double Parser::expr(bool get) { //add y sub
        double left = term(get);
        for (;;) { // ‘‘forever’’
            switch (ts.current().kind) {
            case Lexer::Kind::plus:
                left += term(true);
                break;
            
            case Lexer::Kind::minus:
                left -= term(true);
                break;
                default:
                return left;
            }
        }
    }
}