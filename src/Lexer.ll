%{
#include <iostream>
#include <string>
using namespace std;

#include "Lexer.hpp"
#include "Tokens.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

letra [a-zA-ZñÑáéíóúÁÉÍÓÚ]
letra_ {letra}|_
id {letra_}({letra_}|[0-9])*
ent [0-9]+
notacion [eE][+-]?{ent}
flotante ({ent}"."{ent}?|"."{ent}){notacion}?|{ent}{notacion}

%%
"if"    { return TOK_IF;}
"else"  { return TOK_ELSE;}
"while" { return TOK_WHILE;}
"do"    { return TOK_DO;}
"int"   { return TOK_INT;}
"float" { return TOK_FLOAT;}
"="     { return TOK_ASIG; }
"+"     { return TOK_MAS; }
"*"     { return TOK_MUL; }
"("     { return TOK_LPAR; }
")"     { return TOK_RPAR; }
"["     { return TOK_LCOR; }
"]"     { return TOK_RCOR; }
","     { return TOK_COMA; }
";"     { return TOK_PYC; }
{id}    { return TOK_ID; }
{ent}   { 
            numType = 0;
            return TOK_NUM;
        }
{flotante}   { 
            numType = 1;
            return TOK_NUM;
        }

[ \t\r]+   {}

"\n"    { line++; }
.       { cout<<"ERROR LEXICO "<<yytext<<endl;}

%%
int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}


int Lexer::getType()
{
    return numType;
}

string Lexer::getVal(){
    return yytext;
}
