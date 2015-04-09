#include <iostream>
#include "AvmException.hpp"
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int
main(int ac, char **av)
{
	try {
    	Lexer   lexer(ac, av);
    	lexer.run();
        Parser  parser(lexer.lexemes());
    	parser.run();
    } catch (AvmException& e)
    {
    	std::cout << e.what() << std::endl;
    }
}    