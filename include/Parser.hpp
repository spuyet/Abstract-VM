#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <list>
#include "AvmException.hpp"
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Lexer.hpp"

class Parser
{

public:
    Parser(std::list<Lexeme>& lexemes);
    void    run();

    void    push(std::list<Lexeme>::iterator& it);
    void    pop(std::list<Lexeme>::iterator& it);
    void    dump(std::list<Lexeme>::iterator& it);
    void    assert(std::list<Lexeme>::iterator& it);
    void    add(std::list<Lexeme>::iterator& it);
    void    sub(std::list<Lexeme>::iterator& it);
    void    mul(std::list<Lexeme>::iterator& it);
    void    div(std::list<Lexeme>::iterator& it);
    void    mod(std::list<Lexeme>::iterator& it);
    void    print(std::list<Lexeme>::iterator& it);
    void    exit(std::list<Lexeme>::iterator& it);
    void    end(std::list<Lexeme>::iterator& it);

    ~Parser();
private:
    class ParserException : public AvmException
    {
    public:
        ParserException(const std::string& message)
        : AvmException()
        , _msg(message)
        {

        }
    
        virtual const char* what() const throw ()
        {
            return _msg.c_str();
        }

        virtual ~ParserException() throw (){}
    private:
        std::string         _msg;

    };

    std::list<Lexeme>&            _lexemes;
    std::list<const IOperand*>    _stack;
    std::map<int, void (Parser::*)(std::list<Lexeme>::iterator&)>    _operations;
    OperandFactory                _factory;
};

#endif