//
//
//
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <string>
#include <vector>

#include "excepciones.hh"
#include "file.hh"

#ifndef __utils_h__
#define __utils_h__

#ifdef LOG
#define log(x) std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " << x << std::endl;
#else
#define log(x)
#endif

namespace sis
{
    typedef void (*usof_t)(const char * prg);

    inline bool str_igual (const char * s1, 
			   const char * s2)
    {
	return (std::strcmp(s1, s2) == 0);
    }

    std::string cat (const char * s1, const char * s2);
    char * strdup (const char * str);
    char * strcat (const char * s1,
		   const char * s2);
    std::string buscarRuta (std::string ruta, std::string sep = "/");
    std::string tomarValor (std::string elem, std::string sep = ":");
    std::string tomarRuta (std::string elem, std::string sep = "/");
    void verificarConf (const char * prog, const char * file, usof_t func);
    int convertirInt (std::string ent);
    std::string convertirInt (int i);
    std::string mayusculas (std::string str);
    std::string minusculas (std::string str);

    typedef std::vector<std::string> strings_t;
    void split (std::string str, strings_t & strs, char sep = ' ');

    std::string date ();

    namespace env 
    {
	std::string get (std::string nom);
	std::string user ();

    } // end namespace env

}

#endif // __utils_h__
