#ifndef AVM_EXCEPTION_HPP
# define AVM_EXCEPTION_HPP

class AvmException : public std::exception
{
public:
    AvmException() {};
    AvmException(const AvmException&);
    const AvmException& operator=(const AvmException \&);
    virtual const char* what() const throw ()
    {
        return _msg.c_str();
    }

    virtual ~AvmException() throw (){}
private:
	std::string         _msg;
};

#endif