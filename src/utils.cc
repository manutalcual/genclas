//
//
//
#include "utils.hh"

namespace sis
{

    std::string cat (const char * s1, const char * s2)
    {
	return std::string(s1) + std::string(s2);
    }

    char * strdup (const char * str)
    {
	char * s = new char [std::strlen(str) 
			     + 1];
      
	std::strcpy (s, str);

	return s;
    }

    char * strcat (const char * s1, 
		   const char * s2)
    {
	char * tmp = new char [std::strlen(s1) 
			       + std::strlen(s2)
			       + 1];

	std::strcpy (tmp, s1);
	std::strcat (tmp, s2);

	return tmp;
    }

    std::string buscarRuta (std::string ruta, std::string sep)
    {
	unsigned int pos = ruta.find(sep);
	std::string ret (ruta);

	if (pos != std::string::npos)
	{
	    ret = buscarRuta(ruta.substr(pos + 1));
	}

	return ret;
    }

    std::string tomarValor (std::string elem, std::string sep)
    {
	unsigned int pos = elem.find(sep);
	std::string ret ("");

	if (pos != std::string::npos)
	{
	    ret = elem.substr(pos + 1);
	}

	return ret;
    }

    std::string tomarRuta (std::string ruta, std::string sep)
    {
	unsigned int pos = ruta.find(sep);
	std::string ret (ruta);

	if (pos != std::string::npos)
	{
	    ret = ruta.substr(0, pos);
	}

	return ret;
    }

    void verificarConf (const char * prog, const char * file,
			usof_t func)
    {
	try
	{
	    sis::file f (file);
	}
	catch (const char * ex)
	{
	    func (prog);
	    ::exit (1);
	}
    }

    int convertirInt (std::string ent)
    {
	errno = 0;
	int r = ::strtol(ent.c_str(), NULL, 10);

	if (errno == ERANGE)
	    throw sis::ex_rango("Convesión a entero inválida.");

	return r;
    }

    std::string convertirInt (int i)
    {
	char buf [256];

	::sprintf (buf, "%d", i);

	return buf;
    }

    std::string mayusculas (std::string str)
    {
	std::string s (str);
	
	for (int i = 0; i < s.size(); ++i)
	{
	    s[i] = ::toupper(s[i]);
	}

	return s;
    }

    std::string minusculas (std::string str)
    {
	std::string s;
	
	for (int i = 0; i < str.size(); ++i)
	{
	    s += ::tolower(str[i]);
	}

	return s;
    }

    void split (std::string str, strings_t & strs, char sep)
    {
	while (str.find(sep) != std::string::npos)
	{
	    std::string p;

	    if (str.find(sep) != std::string::npos)
	    {
		p = str.substr(0, str.find(sep));
		str = str.substr(str.find(sep) + 1);
		strs.push_back (p);
	    }
	}
    }

    std::string date ()
    {
	time_t t = ::time(0);
	std::string d (::ctime(&t));
	d = d.substr(0, d.size() - 1); // Eliminar el salto de línea
	return d;
    }


    namespace env 
    {
	std::string get (std::string nom)
	{
	    std::string r;
	    char * pr = ::getenv(nom.c_str());
	    if (pr)
		r = pr;
	    return r;
	}

	std::string user ()
	{
	    return get("USER");
	}

    } // end namespace env



}


