#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>
#include <map>

enum token {
    PUSH = 258,
    POP = 259,
    DUMP = 260,
    ASSERT = 261,
    ADD = 262,
    SUB = 263,
    MUL = 264,
    DIV = 265,
    MOD = 266,
    PRINT = 267,
    EXIT = 268,
    END = 269,
    COMMENT = 270,
    EOL = 271,
    INT8 = 272,
    INT16 = 273,
    INT32 = 274,
    FLOAT = 275,
    DOUBLE = 276,
    ERROR = 277
};

struct Lexeme
{
    token               type;
    const std::string   value;
};

class Lexer
{
public:
    Lexer(int ac, char** av);
    void                run();
    std::string         getValue(char* str, token type);
    ~Lexer();
    std::list<Lexeme>&  lexemes();
private:

    class LexerException : public std::exception
    {
    public:
        LexerException(const std::string& message)
        : _msg(message)
        {

        }
    
        virtual const char* what() const throw ()
        {
            return _msg.c_str();
        }

        virtual ~LexerException() throw (){}
    private:
        std::string         _msg;

    };
    std::list<Lexeme>                               _lexemes;
    static  std::map<token, const std::string>      _masks;
};

#endif