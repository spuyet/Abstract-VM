#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>

#include <string>
#include <sstream>
#include <float.h>
#include <limits.h>
#include <math.h>
#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
public:

	Operand(std::string const & value, eOperandType type, int precision, const OperandFactory* factory)
	: _type(type)
	, _precision(precision)
	, _factory(factory)
	, _str(value)
	{
		try
		{
			auto v = (type < Float) ? std::stoll(value) : std::stold(value);
			if (((type < Float) ? hasOverflow<long long>(v, type) : hasOverflow<long double>(v, type)))
				throw OperandException("Overflow or underflow !");
			_value = static_cast<T>(v);
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
	}

	int getPrecision( void ) const // Precision of the type of the instance
	{
		return _precision;
	}

	eOperandType getType( void ) const // Type of the instance
	{
		return _type;
	}

	IOperand const * operator+( IOperand const & rhs ) const // Sum
	{
		eOperandType type = (_precision >= rhs.getPrecision()) ? _type : rhs.getType();
		try
		{
			auto r = (type < Float) ? std::stoll(_str) + std::stoll(rhs.toString()) : std::stold(_str) + std::stold(rhs.toString());
			if (((type < Float) ? hasOverflow<long long>(r, type) : hasOverflow<long double>(r, type)))
				throw OperandException("Overflow or underflow !");
			std::stringstream ss (std::stringstream::out);
			ss << r;
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
		return (0);
	}

	IOperand const * operator-( IOperand const & rhs ) const // Difference
	{
		eOperandType type = (_precision >= rhs.getPrecision()) ? _type : rhs.getType();
		try
		{
			auto r = (type < Float) ? std::stoll(_str) - std::stoll(rhs.toString()) : std::stold(_str) - std::stold(rhs.toString());
			if (((type < Float) ? hasOverflow<long long>(r, type) : hasOverflow<long double>(r, type)))
				throw OperandException("Overflow or underflow !");
			std::stringstream ss (std::stringstream::out);
			ss << r;
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
		return (0);
	}

	IOperand const * operator*( IOperand const & rhs ) const // Product
	{
		eOperandType type = (_precision >= rhs.getPrecision()) ? _type : rhs.getType();
		try
		{
			auto r = (type < Float) ? std::stoll(_str) * std::stoll(rhs.toString()) : std::stold(_str) * std::stold(rhs.toString());
			if (((type < Float) ? hasOverflow<long long>(r, type) : hasOverflow<long double>(r, type)))
				throw OperandException("Overflow or underflow !");
			std::stringstream ss (std::stringstream::out);
			ss << r;
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
		return (0);
	}

	IOperand const * operator/( IOperand const & rhs ) const // Quotient
	{
		eOperandType type = (_precision >= rhs.getPrecision()) ? _type : rhs.getType();
		try
		{
			if (std::stold(rhs.toString()) == 0)
				throw OperandException("Division by zero !");
			auto r = (type < Float) ? std::stoll(_str) / std::stoll(rhs.toString()) : std::stold(_str) / std::stold(rhs.toString());
			if (((type < Float) ? hasOverflow<long long>(r, type) : hasOverflow<long double>(r, type)))
				throw OperandException("Overflow or underflow !");
			std::stringstream ss (std::stringstream::out);
			ss << r;
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
		return (0);
	}

	IOperand const * operator%( IOperand const & rhs ) const // Modulo
	{
		eOperandType type = (_precision >= rhs.getPrecision()) ? _type : rhs.getType();
		try
		{
			if (std::stold(rhs.toString()) == 0)
				throw OperandException("Modulo by zero !");
			auto r = (type < Float) ? std::stoll(_str) % std::stoll(rhs.toString()) : fmod(std::stold(_str), std::stold(rhs.toString()));
			if (((type < Float) ? hasOverflow<long long>(r, type) : hasOverflow<long double>(r, type)))
				throw OperandException("Overflow or underflow !");
			std::stringstream ss (std::stringstream::out);
			ss << r;
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor)
		{
			oor.what();
		}
		return (0);
	}

	std::string const & toString( void ) const // String representation of the instance
	{
		return (_str);
	}

	template <typename U>
	bool	hasOverflow(U r, eOperandType type) const
	{
		switch (type)
		{
			case (Int8):
				return (r > SCHAR_MAX || r < SCHAR_MIN);
			case (Int16):
				return  (r > SHRT_MAX || r < SHRT_MIN);
			case (Int32):
				return (r > INT_MAX || r < INT_MIN);
			case (Float):
				return (r > FLT_MAX || r < -FLT_MAX);
			case (Double):
				return (r > DBL_MAX || r < -DBL_MAX);
			break;
		}
		return (true);
	}

	~Operand( void )
	{

	}

private:
	class OperandException : public std::exception
	{
	public:
		OperandException(const std::string& message)
		: _msg(message)
		{

		}
	
	  	virtual const char* what() const throw ()
	  	{
       		return _msg.c_str();
    	}

		virtual ~OperandException() throw (){}
	private:
		std::string			_msg;

	};

	T										_value;
	eOperandType							_type;
	int										_precision;
	const OperandFactory*					_factory;
	const std::string						_str;
};

#endif