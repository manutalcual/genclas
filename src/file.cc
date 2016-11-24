//
//
//
//
#include "file.hh"

#include "utils.hh"


namespace sis
{

    ex_noxfile::ex_noxfile (std::string str)
	: _e (str)
    {
    }
    
    ex_noxfile::ex_noxfile (const ex_noxfile & e)
	: _e (e._e)
    {
    }
    
    ex_noxfile::operator const char * ()
    {
	return _e.c_str();
    }

    file::file (const char * nombre)
	:	_nombre (new char [::strlen(nombre) + 1])
    {
	if (! _nombre)
	    throw "No hay memoria";
	
	if (::stat (nombre, &_st) != 0) {
	    _st.st_size = 0;
	    throw ex_noxfile(sis::cat("El archivo ", nombre) + " no existe.");
	}
	
	::strcpy (_nombre, nombre);
    }

    file::~file ()
    {
	delete [] _nombre;
    }

    const char * file::nombre () const
    {
	return _nombre;
    }

    size_t file::size () const
    {
	return _st.st_size;
    }

    char * file::cargar ()
    {
	char * buf = 0;
	
	if (_st.st_size) 
	{

	    buf = new char [_st.st_size];
		
	    FILE * f = ::fopen(_nombre, "rb");
		
	    if (! f)
		return 0;
		
	    int len = 0;
	    if ( 
		(len = ::fread(buf, 1, _st.st_size, f)) 
		!= _st.st_size
		) 
	    {
		::fclose (f);
		return 0;
	    }
		
	    ::fclose (f);
	} else {
	    std::cerr << "El tamaño del archivo '" << _nombre << "' es 0." << std::endl;
	}
	
	return buf;
    }

} // end namespace sis
