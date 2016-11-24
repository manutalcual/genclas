//
// Clase: parser Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Wed Mar 15 16:29:27 2006
// Time-stamp: <11-ago-2006 13:17:48 mcano>
//
// Includes
//
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>

#include "excepciones.hh"
#include "utils.hh"
#include "config.hh"
#include "comandos.hh"

#ifndef __parser_h__
#define __parser_h__


namespace sis {


  class parser
  {
  public:
	parser (std::string fname, std::string clase,
            sis::config::bloque & bl);
	~parser ();
	operator bool ();
	std::string & resultado ();
  protected:
  private:
	sis::config::bloque & _bloque;
	bool _ok;
	char * _str;
	int _i;
	int _size;
	std::string _buf;
	std::string _clase;

	bool analiza ();
	std::string escapa (int & i);
    std::string escapaComando (sis::config::bloque * blk, int & i);
	std::string skipComando (int & i);
	std::string parseComando (int & i);

	std::string comandoFor (sis::config::bloque * blk, 
                            std::string nom, int & i);
	std::string comandoDo (sis::config::bloque * blk, 
                           IComando * com, int & pos);
	std::string comandoWhile (sis::config::bloque * blk, 
                              std::string nom, int & i);
  };

} // end namespace sis


#endif // __parser_h__


