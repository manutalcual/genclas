//
// Clase: options_parser Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Wed Mar  8 11:11:12 2006
// Time-stamp: <15-mar-2006 12:34:59 mcm014es>
//
//
// Includes
//
#include "options_parser.hh"

namespace sis {


    options_parser::options_parser (int argc, char ** argv)
	: _argc (argc),
	  _argv (argv),
	  _ok (true)
    {
	for (int i = 1; i < argc; ++i)
	{
	    std::string opt = argv[i];
	    std::string opt_name (opt);
	    std::string opt_value;

	    if (opt.find("=") == std::string::npos)
	    {
		if (opt[0] == '-' && opt[1] != '-')
		    opt_name = opt.substr(1);
		else if (opt[0] == '-' && opt[1] == '-')
		    opt_name = opt.substr(2);

		_opts[opt_name] = "true";
	    }
	    else
	    {
		if (opt[0] != '-')
		    opt_name = opt.substr(0, opt.find("="));
		else if (opt[1] != '-')
		    opt_name = opt.substr(1, opt.find("=") - 1); // -1
								 // por el 
		                                                 // guion '-'
		else
		    opt_name = opt.substr(2, opt.find("=") - 2); // -2
								 // por los 
                                                                 // guiones '--'

		opt_value = opt.substr(opt.find("=") + 1);
		_opts[opt_name] = opt_value;

	    }
	}
    }

    options_parser::~options_parser ()
    {
    }

    void options_parser::add_mandatory (std::string opt)
    {
	_ok = false;
	_mand.push_back (opt);
    }

    std::string options_parser::operator [] (std::string key)
    {
	return _opts[key];
    }

    std::string options_parser::operator [] (const char * key)
    {
	return _opts[key];
    }

    optsmap_t & options_parser::options ()
    {
	return _opts;
    }

    options_parser::operator bool ()
    {
	mandatory_t::iterator ib = _mand.begin();
	mandatory_t::iterator ie = _mand.end();

	_ok = true;
	for (; ib != ie; ++ib)
	{
	    if (_opts[(*ib)] == "")
	    {
		_faltan.push_back (*ib);
		_ok = false;
	    }
	}

	return _ok;
    }

    mandatory_t & options_parser::parametros_faltan ()
    {
	return _faltan;
    }


} // end namespace sis


