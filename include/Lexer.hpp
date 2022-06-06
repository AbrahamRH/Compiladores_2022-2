#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <string>
using namespace std;

class Lexer : public yyFlexLexer
{
public:
    Lexer(std::istream *in) : yyFlexLexer(in){};

    using FlexLexer::yylex;
    virtual int yylex();
    virtual int getLine();
    virtual int getType();    
    virtual std::string getVal();
private:
    const int ERROR = -1;
    int line=1;
    int numType;
};

#endif /* __LEXER_HPP__ */
