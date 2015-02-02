#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
{
		create[Int8] = &OperandFactory::createInt8;
		create[Int16] = &OperandFactory::createInt16;
		create[Int32] = &OperandFactory::createInt32;
		create[Float] = &OperandFactory::createFloat;
		create[Double] = &OperandFactory::createDouble;
}

IOperand const*
OperandFactory::createOperand(eOperandType type, std::string const& value) const
{
	IOperand const* (OperandFactory::*f)(std::string const & value) const;
	f = create.at(type);
	return ((*this.*f)(value));
}

IOperand const*
OperandFactory::createInt8( std::string const & value ) const
{
	return (new Int8(value));
}

IOperand const*
OperandFactory::createInt16( std::string const & value ) const
{
	return (new Int16(value));
}

IOperand const*
OperandFactory::createInt32( std::string const & value ) const
{
	return (new Int32(value));
}

IOperand const*
OperandFactory::createFloat( std::string const & value ) const
{
	return (new Float(value));
}

IOperand const*
OperandFactory::createDouble( std::string const & value ) const
{
	return (new Double(value));
}

OperandFactory::~OperandFactory()
{

}