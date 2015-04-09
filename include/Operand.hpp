#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <float.h>
#include <limits.h>
#include <math.h>
#include "AvmException.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
public:

	Operand();
	Operand(const Operand&);
	const Operand& operator=(const Operand&);

	Operand(std::string const & value, eOperandType type, int precision, const OperandFactory* factory)
	: _type(type)
	, _precision(precision)
	, _factory(factory)
	{
		try
		{
			if (type < Float)
			{
				long long v = std::stoll(value);
				if (hasOverflow<long long>(v, type))
					throw OperandException("Overflow or underflow !");
				_value = static_cast<T>(v);
				std::stringstream ss(std::stringstream::out);
				ss << std::setprecision(precision) << v;
				_str = ss.str();
			}
			else
			{
				long double	v = std::stold(value);
				if (hasOverflow<long double>(v, type))
					throw OperandException("Overflow or underflow !");
				_value = static_cast<T>(v);
				std::stringstream ss(std::stringstream::out);
				ss << std::setprecision(precision) << v;
				_str = ss.str();
			}
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
		eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try
		{
			std::stringstream ss (std::stringstream::out);
			if (type < Float)
			{
				long long r = std::stoll(_str) + std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << r;
			}
			else
			{
				long double r = std::stold(_str) + std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << std::setprecision(precision) << r;
			}
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
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try
		{
			std::stringstream ss (std::stringstream::out);
			if (type < Float)
			{
				long long r = std::stoll(_str) - std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << r;
			}
			else
			{
				long double r = std::stold(_str) - std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << std::setprecision(precision) << r;
			}
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
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();

		try
		{
			std::stringstream ss(std::stringstream::out);
			if (type < Float)
			{
				long long r = std::stoll(_str) * std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << r;
			}
			else
			{
				long double r = std::stold(_str) * std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << std::setprecision(precision) << r;
			}
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
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try
		{
			if (std::stold(rhs.toString()) == 0)
				throw OperandException("Division by zero !");
			std::stringstream ss(std::stringstream::out);
			if (type < Float)
			{
				long long r = std::stoll(_str) / std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << r;
			}
			else
			{
				long double r = std::stold(_str) / std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << std::setprecision(precision) << r;
			}
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
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try
		{
			if (std::stold(rhs.toString()) == 0)
				throw OperandException("Modulo by zero !");
			std::stringstream ss(std::stringstream::out);
			if (type < Float)
			{
				long long r = std::stoll(_str) % std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << r;
			}
			else
			{
				long double r = fmod(std::stold(_str), std::stold(rhs.toString()));
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow or underflow !");
				ss << std::setprecision(precision) << r;
			}
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

	std::string	removeTrailingZeros(std::string s) const
	{
		for(int i = s.length() - 1; i >= 0; i--)
		{
			if (s[i] == '0')
				s.erase(s.end() - 1);
			else
				break;
		}
		return s;
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
	class OperandException : public AvmException
	{
	public:
		OperandException(const std::string& message)
		: AvmException()
		, _msg(message)
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
	std::string								_str;
};

#endif