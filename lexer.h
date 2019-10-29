#ifndef CALCULADORA_LEXER_H
#define CALCULADORA_LEXER_H
#include<string>
#include<cctype>
#include<iostream>
#include <sstream>
#include "error.h"

namespace Lexer {
    enum class Kind : char {
        NAME, NUMBER, END,
        PLUS = '+', 
        SUB = '-', 
        MULT = '*', 
        DIV = '/', 
        PRINT = ';', 
        ASSIGN = '=', 
        LP = '(', 
        RP = ')',
        EXP = '^'
    };

    struct Token { 
        Kind kind;
        std::string string_value;
        double number_value;
    };

    class Token_stream { 
        public:
            Token_stream(std::istream& s) : ip{&s}, owns{false}, ct{Kind::END} { }
            Token_stream(std::istream* p) : ip{p}, owns{true}, ct{Kind::END} { }
            
            ~Token_stream() { close(); }
            
            Token get(){ // read and return next token
                char ch = 0;
                do{
                    if(!ip->get(ch))
                    return ct={Kind::END};
                }
                while (ch!='\n' && isspace(ch));
                switch (ch) {
                case ';':
                case '\n':
                    return ct={Kind::PRINT};  // end of expression; print
                case '*':
                case '/':
                case '+':
                case '-':
                case '(':
                case ')':
                case '^':
                case '=':
                    return ct = {static_cast<Kind>(ch)};
                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                case '.':
                    ip -> putback(ch); // put the first digit (or .) back into the input stream
                    *ip >> ct.number_value; // read number into ct
                    ct.kind = Kind::NUMBER;
                    return ct;
                default: // name, name =, or error
                    if (isalpha(ch)) {
                        ct.string_value = ch;
                        while (ip->get(ch) && isalnum(ch))
                            ct.string_value += ch; // append ch to end of string_value
                            ip->putback(ch);
                            return ct={Kind::NAME};
                    }
                error("bad token");
                return ct={Kind::PRINT};
                }
            } 

            Token& current(){ // most recently read token
                return ct;
            }
            
            void set_input(std::istream& s) { close(); ip = &s; owns=false; }
            void set_input(std::istream* p) { close(); ip = p; owns = true; }
        private:
            void close() { if (owns) delete ip; }
            
            std::istream* ip; // pointer to an input stream
            bool owns; // does the Token_stream own the istream?
            
            Token ct {Kind::END}; // current token
    };

} 
extern Lexer::Token_stream ts;
#endif