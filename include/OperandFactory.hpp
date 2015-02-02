#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include <string>
#include <map>
#include "IOperand.hpp"

class OperandFactory
{
public:
	OperandFactory();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	~OperandFactory();

private:

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	std::map<eOperandType, IOperand const* (OperandFactory::*)(std::string const & value) const>	create;

};

#endif