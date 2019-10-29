#include "lexer.h"
#include "parser_imp.h"
#include "table.h"
#include "error.h"
#include <iostream>

Lexer::Token_stream ts;
using namespace Lexer;
using namespace Error;

namespace Parser{
    double Parser::prim(bool get) {
        if (get) ts.get(); // read next token
            switch (ts.current().kind) {
            case Kind::number: { // floating-point constant
                double v = ts.current().number_value;
                ts.get();
                return v;

            }
            case Kind::name: {
                double& v = Table::table[ts.current().string_value]; // find the corresponding
                if (ts.get().kind == Kind::assign) 
                    v = expr(true); // ’=’ seen: assignment
                    return v;
            }
            case Kind::minus: // unar y minus
                return -prim(true);
            case Kind::lp: {
                auto e = expr(true);
                if (ts.current().kind != Kind::rp) 
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
            case Kind::mul:
                left *= prim(true);
                break;
            case Kind::div:
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
            case Kind::plus:
                left += term(true);
                break;
            
            case Kind::minus:
                left -= term(true);
                break;
                default:
                return left;
            }
        }
    }
}