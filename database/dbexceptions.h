#ifndef DBEXCEPTIONS_H
#define DBEXCEPTIONS_H

#include <exception>

class DBException : public std::exception
{
public:
	DBException(const std::string &s) throw()
	{
		m_s = s;
	}
	~DBException() throw() {}
	virtual const char * what() const throw()
	{
		return m_s.c_str();
	}
protected:
	std::string m_s;
};


#endif
