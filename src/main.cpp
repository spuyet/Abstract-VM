#include <iostream>
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int
main(int ac, char **av)
{
    Lexer   lexer(ac, av);
    lexer.run();
    Parser  parser(lexer.lexemes());
    parser.run();
}    