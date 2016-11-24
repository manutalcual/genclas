//
// Clase: options_parser Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Wed Mar  8 11:11:12 2006
// Time-stamp: <14-mar-2006 17:43:43 mcm014es>
//
// Includes
//
#include <map>
#include <string>
#include <iostream>
#include <vector>


#ifndef __options_parser_h__
#define __options_parser_h__


namespace sis {

    typedef std::map<std::string, std::string> optsmap_t;
    typedef std::pair<std::string, std::string> option_t;
    typedef std::vector<std::string> mandatory_t;

    class options_parser
    {
    public:
	options_parser (int argc, char ** argv);
	~options_parser ();
	void add_mandatory (std::string opt);
	std::string operator [] (std::string key);
	std::string operator [] (const char * key);
	optsmap_t & options ();
	mandatory_t & parametros_faltan ();
	operator bool ();
    protected:
    private:
	int _argc;
	char ** _argv;
	bool _ok;
	optsmap_t _opts;
	mandatory_t _mand;
	mandatory_t _faltan;
    };


} // end namespace sis


#endif // __options_parser_h__


