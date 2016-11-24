//
// Clase: comandos Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Fri Apr  7 17:06:05 2006
// Time-stamp: <11-abr-2006 12:14:13 mcm014es>
//
// Includes
//
#include <string>
#include "utils.hh"

#ifndef __comandos_h__
#define __comandos_h__

namespace sis
{
    class IComando
    {
    public:
	virtual char operator << (char) = 0;
	virtual std::string operator << (std::string) = 0;
	virtual std::string as_string () = 0;
    };

    namespace com
    {
	IComando * factoria (std::string nombre);
    }

    class base_comando : public IComando
    {
	friend IComando * com::factoria (std::string nombre);
    public:
	virtual ~base_comando () {}
	virtual char operator << (char ch) { return ch; }
	virtual std::string operator << (std::string buf) { return buf; }
	virtual std::string as_string () {} ;
    protected:
	base_comando ();
    };

    class ucase : public base_comando
    {
    public:
	ucase ();
	ucase (const ucase & c);
	~ucase ();
	virtual char operator << (char ch);
	virtual std::string operator << (std::string buf);
	virtual std::string as_string ();
    private:
	std::string _buf;
    };

} // end namespace sis

#endif // __comandos_h__


