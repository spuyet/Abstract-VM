#include <iostream>
#include <regex>
#include "Lexer.hpp"

extern int      yylex(void);
extern FILE*    yyin;
extern char*    yytext;
extern int      yyleng;

Lexer::Lexer(int ac, char** av)
: _lexemes(0)
{
    if (ac > 2)
        throw LexerException("Lexer: Too much args.");
    if (ac == 2)
    {
        yyin = fopen(av[1], "r");
        if (!yyin)
            throw LexerException("Lexer: Cannot open file.");
    }
}

void
Lexer::run()
{
    int tok;

    while ((tok = yylex()))
    {
        if (tok == ERROR)
            throw LexerException("Illegal instruction");
        if (tok == END)
            break;
        const std::string value = yytext;
        _lexemes.push_back({static_cast<token>(tok), value});
    }
}

std::list<Lexeme>&
Lexer::lexemes()
{
    return _lexemes;
}

Lexer::~Lexer()
{

}