#ifndef OPERAND_H
#define OPERAND_H

#include "IOperand.hpp"

template <int E>
class Operand : public IOperand
{
public:
	Operand(std::string const & value);
	int getPrecision( void ) const; // Precision of the type of the instance
	eOperandType getType( void ) const; // Type of the instance
	IOperand const * operator+( IOperand const & rhs ) const; // Sum
	IOperand const * operator-( IOperand const & rhs ) const; // Difference
	IOperand const * operator*( IOperand const & rhs ) const; // Product
	IOperand const * operator/( IOperand const & rhs ) const; // Quotient
	IOperand const * operator%( IOperand const & rhs ) const; // Modulo
	std::string const & toString( void ) const; // String representation of the instance
	~Operand( void );
private:

	eOperandType		_type;
	int					_precision;
};

#endif