//
//
//
#include "excepciones.hh"

namespace sis
{

    ex::ex ()
	: _str (0)
    {
    }

    ex::ex (const char * str)
	: _str (0)
    {
	int i = 0;
	const char * p = str;

	while (*p) {
	    ++i;
	    ++p;
	}

	_str = new char [i + 1];
	i = 0;
	p = str;

	while (*p) {
	    _str[i] = *p;
	    ++i;
	    ++p;
	}
	_str[i] = '\0';
    }

    ex::ex (const ex & e)
	: _str (0)
    {
	int i = 0;
	const char * p = e._str;

	while (*p) {
	    ++i;
	    ++p;
	}

	_str = new char [i + 1];
	p = e._str;
	i = 0;

	while (*p) {
	    _str[i] = *p;
	    ++i;
	    ++p;
	}
	_str[i] = '\0';
    }

    ex::~ex ()
    {
	delete [] _str;
	_str = 0;
    }

    ex::operator const char * ()
    {
	return _str;
    }

}
