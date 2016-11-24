//
// Clase: comandos Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Fri Apr  7 17:06:05 2006
// Time-stamp: <10-Aug-2006 22:59:33 manuel>
//
//
// Includes
//
#include "comandos.hh"

namespace sis
{
    namespace com
    {
	IComando * factoria (std::string nombre)
	{
	    if (nombre == "upcase")
		return new ucase;
	    return NULL;
	}
    }

    base_comando::base_comando ()
    {
    }

    ucase::ucase ()
    {
    }

    ucase::ucase (const ucase & c)
	: _buf (c._buf)
    {
    }

    ucase::~ucase ()
    {
    }

    char ucase::operator << (char ch)
    {
	_buf += ::toupper(ch);
	return ch;
    }

    std::string ucase::operator << (std::string buf)
    {
	std::string b = mayusculas(buf);
	_buf += b.c_str();
	return buf;
    }

    std::string ucase::as_string ()
    {
	return _buf;
    }

} // end namespace sis
