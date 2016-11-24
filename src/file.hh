//
//
//
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

#include "excepciones.hh"

#ifndef __file_h__
#define __file_h__

namespace sis {

    class ex_noxfile : public ex
    {
    public:
	ex_noxfile (std::string e);
	ex_noxfile (const ex_noxfile & e);
	operator const char * ();
    private:
	std::string _e;
    };
	
    class file
    {
    public:
	file (const char * name);
	~file ();
	const char * nombre () const;
	size_t size () const;
	char * cargar ();
    protected:
    private:
	struct stat _st;
	char * _nombre;
	unsigned char * _buffer;
    };

} // end namespace sis

#endif // __file_h__
