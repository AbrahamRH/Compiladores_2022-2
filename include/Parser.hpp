#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include <string>
#include <sstream>
#include <queue>
using namespace std;
#include "Tokens.hpp"
#include "Lexer.hpp"
#include "Action.hpp"
#include "Atributos.hpp"
#include "Generator.hpp"

class Parser{
private:
    TOKEN token;
    void eat(TOKEN t);
    void error(string  msg);
    Lexer *lexer;
    Action action;
    Generator gen;
    map<TOKEN, string> tokens;
    queue<TOKEN> tokens_enum;
    queue<string> tokens_string;
    queue<int> tokens_numType;
    queue<int> tokens_lines;

public:
    Parser();
    Parser(Lexer *lex, string filename);
    bool parse();
    void p();
    void d();
    void r();
    void l(int ltipo);
    void l_(int tipo);
    int t();
    int b();
    int a(int base);
    void r_();
    void s();
    void z();
    void c(string id);    
    TOKEN getCurrentToken();
    expresion e();
    expresion e_(expresion E_);
    expresion g();
    expresion g_(expresion G_);
    expresion f();
    expresion f_(expresion F_);
    expresion y(expresion id);
    arreglo y_(arreglo Y_);
    
};

#endif // !__PARSER_HPP__
