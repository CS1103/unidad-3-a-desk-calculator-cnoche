#ifndef CALCULADORA_PARSER_H
#define CALCULADORA_PARSER_H
#include <iostream>
#include <cmath>
#include "lexer.h"
#include "table.h"

using namespace Lexer;

double expr(bool get);
double term(bool get);
double prim(bool get);

double expr(bool get) { //add y sub
    double left = term(get);
    while(true) { 
        switch (ts.current().kind) {
        case Kind::PLUS:
            left += term(true);
            break;
        
        case Kind::SUB:
            left -= term(true);
            break;
            default:
            return left;
        }
    }
}

double term(bool get) { //mult y div y exp
    double left = prim(get);
    while(true) {
        switch (ts.current().kind) {
        case Kind::MULT:
            left *= prim(true);
            break;
        case Kind::DIV:
            if (auto d = prim(true)) {
                left /= d;
                break;
            }
            return error("divide by 0");
        case Kind::EXP:
            left = pow(left, prim(true));
            break;
        default:
            return left;
        }
    }
}

double prim(bool get) {
    if (get) ts.get(); // read next token
        switch (ts.current().kind) {
        case Kind::NUMBER: { // floating-point constant
            double v = ts.current().number_value;
            ts.get();
            return v;

        }
        case Kind::NAME: {
            double& v = Table::table[ts.current().string_value]; // find the corresponding
            if (ts.get().kind == Kind::ASSIGN) 
                v = expr(true); // ’=’ seen: assignment
                return v;
        }
        case Kind::SUB: // suma y minus
            return -prim(true);
        case Kind::LP: {
            auto e = expr(true);
            if (ts.current().kind != Kind::RP) 
                return error("')' expected");
                ts.get(); // eat ’)’
                return e;
        }
    default:
        return error("primary expected");
    }
}

#endif