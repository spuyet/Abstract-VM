#include <iostream>
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

int
main()
{
	OperandFactory	factory;

	std::cout << "Hello world!" << std::endl;
	const Operand<float> *op = static_cast<const Operand<float>*>(factory.createOperand(Float, "4.565454545454545"));
	const Operand<float> *op1 = static_cast<const Operand<float>*>(factory.createOperand(Float, "2.23"));

	std::cout << (*op + *op1)->toString() << std::endl ;
}