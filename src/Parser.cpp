#include <iostream>
#include "Parser.hpp"


Parser::Parser(std::list<Lexeme>& lexemes)
: _lexemes(lexemes)
{
    _operations[0] = &Parser::push;
    _operations[1] = &Parser::pop;
    _operations[2] = &Parser::dump;
    _operations[3] = &Parser::assert;
    _operations[4] = &Parser::add;
    _operations[5] = &Parser::sub;
    _operations[6] = &Parser::mul;
    _operations[7] = &Parser::div;
    _operations[8] = &Parser::mod;
    _operations[9] = &Parser::print;
    _operations[10] = &Parser::exit;
}

void
Parser::run()
{
    for (std::list<Lexeme>::iterator it = _lexemes.begin() ; it != _lexemes.end() ; it++)
    {
        if (it->type > END)
            continue;
        void (Parser::*f)(std::list<Lexeme>::iterator &);
        // std::cout << it->type - PUSH << std::endl;
        f = _operations.at(it->type - PUSH);
        (*this.*f)(it);
        // std::cout << "stack.size = " << _stack.size() << std::endl;
    }
}

void
Parser::push(std::list<Lexeme>::iterator& it)
{
    std::list<Lexeme>::iterator next = it;
    next++;
    // if (next == _lexemes.end()
    //     || next->type < INT8 
    //     || next->type > FLOAT)
    //     throw ParserException("Value error !");
    // std::cout << next->type << std::endl;
    // std::cout << next->value << std::endl;
    _stack.push_front(_factory.createOperand(static_cast<eOperandType>(next->type - INT8), next->value));
}

void
Parser::pop(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() == 0)
        throw ParserException("Pop instruction on empty stack");
    _stack.pop_front();
}

void
Parser::dump(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() == 0)
        throw ParserException("Pop instruction on empty stack");
    std::list<const IOperand*>::iterator itr;

    for (itr = _stack.begin(); itr != _stack.end(); ++itr)
        std::cout << (*itr)->toString() << std::endl;
}

void
Parser::assert(std::list<Lexeme>::iterator& it)
{
    if (_stack.size() == 0)
        throw ParserException("Assert instruction on empty stack");
    std::list<Lexeme>::iterator next = it;
    next++;
    const IOperand* op = *(_stack.begin());
    if (op->toString() != next->value)
        throw ParserException("Assert instruction with different value");
    if (op->getType() != next->type - INT8)
        throw ParserException("Assert instruction with different type");
}

void
Parser::add(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() < 2)
        throw ParserException("Add on stack with less than two values");
    const IOperand* op1 = *(_stack.begin());
    const IOperand* op2 = *(++_stack.begin());
    const IOperand* r  = *op1 + *op2;
    _stack.pop_front();
    _stack.pop_front();
    _stack.push_front(r);
}

void
Parser::sub(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() < 2)
        throw ParserException("Sub on stack with less than two values");
    const IOperand* op1 = *(_stack.begin());
    const IOperand* op2 = *(++_stack.begin());
    const IOperand* r  = *op2 - *op1;
    _stack.pop_front();
    _stack.pop_front();
    _stack.push_front(r);
}

void
Parser::mul(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() < 2)
        throw ParserException("Mul on stack with less than two values");
    const IOperand* op1 = *(_stack.begin());
    const IOperand* op2 = *(++_stack.begin());
    const IOperand* r  = *op1 * *op2;
    _stack.pop_front();
    _stack.pop_front();
    _stack.push_front(r);
}

void
Parser::div(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() < 2)
        throw ParserException("Div on stack with less than two values");
    const IOperand* op1 = *(_stack.begin());
    const IOperand* op2 = *(++_stack.begin());
    const IOperand* r  = *op2 / *op1;
    _stack.pop_front();
    _stack.pop_front();
    _stack.push_front(r);
}

void
Parser::mod(std::list<Lexeme>::iterator& it)
{
    (void)it;
    if (_stack.size() < 2)
        throw ParserException("Mod on stack with less than two values");
    const IOperand* op1 = *(_stack.begin());
    const IOperand* op2 = *(++_stack.begin());
    const IOperand* r  = *op2 % *op1;
    _stack.pop_front();
    _stack.pop_front();
    _stack.push_front(r);
}

void
Parser::print(std::list<Lexeme>::iterator& it)
{
    (void)it;
}

void
Parser::exit(std::list<Lexeme>::iterator& it)
{
    (void)it;
    std::exit(0);
}

Parser::~Parser()
{

}