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
        {
            std::string error(yytext);
            std::cerr << "Unknow instruction: \"" << error << "\"" << std::endl;
            throw LexerException("Illegal instruction");
        }
        const std::string value = ((tok > EOL) ? getValue(yytext, static_cast<token>(tok)) : yytext);
        _lexemes.push_back({static_cast<token>(tok), value});
    }
}


std::string
Lexer::getValue(char* str, token type)
{
    std::string subject(str);
    std::regex re(_masks[type]);
    std::smatch match;
    
    std::regex_search(subject, match, re) && match.size();
    return match.str(1);
}

std::list<Lexeme>&
Lexer::lexemes()
{
    return _lexemes;
}


Lexer::~Lexer()
{

}

std::map<token, const std::string>
Lexer::_masks = 
{
    { DOUBLE, "double[(]([0-9]+.[0-9]+)[)]" },
    { INT8, "int8[(]([0-9]+)[)]" },
    { INT16, "int16[(]([0-9]+)[)]" },
    { INT32, "int32[(]([0-9]+)[)]" },
    { FLOAT, "float[(]([0-9]+.[0-9]+)[)]"},
};