//
//
//
#include "config.hh"


namespace sis {

  ex_nobloque::ex_nobloque (std::string str)
	: _er (str)
  {
  }
    
  ex_nobloque::ex_nobloque (const ex_nobloque & e)
	: _er (e._er)
  {
  }
    
  ex_nobloque::operator const char * ()
  {
	return _er.c_str();
  }

  config::config (std::string nombre)
	:	_nombre (nombre),
		_num_buf (0),
		_len_buf (0),
		_indice (0),
		_lineas (1)
  {

	try {
      file f (_nombre.c_str());
			
      _buf = f.cargar ();
			
      if (_buf) {
		_len_buf = f.size();
      } else {
		_buf = NULL;
		_len_buf = 0;
      }
	} catch (const char * ex) {
      _buf = NULL;
      _len_buf = 0;
      throw ex;
	} catch (...) {
      _buf = NULL;
      _len_buf = 0;
      throw;
	}
	
	_token[0] = '\0';
	_valor[0] = '\0';

	parse ();
		
  }
	
  config::~config ()
  {
	vector<bloque *>::iterator itbloque = _bloques.begin();
		
	for (; itbloque != _bloques.end(); ++itbloque) 
      {
	    delete (*itbloque);
      }
  }
	
  void config::parse ()
  {
	int st = 0;
	int ambito = 0;
		
	while (!finBuffer() && st != 5) 
      {

	    switch (st) {
	    case 0: {
          if (isSpace(_buf[_indice]) 
              || match(_buf[_indice], '#')) 
            {
              skipSpaces ();
              --_indice;
            } 
          else 
            {
              parseToken ();

              if (! hayToken()) 
                {
                  return;
                }

              _bloques.push_back (new bloque (_token));
              _blks.push_back (_bloques.back());
              st = 1;
            }
	    }
          break;
	    case 1: {
          if (isSpace(_buf[_indice]) 
              || match(_buf[_indice], '#')) 
            {
              skipSpaces ();
              --_indice;
            } 
          else if (match(_buf[_indice], '{')) 
            {
              ++ambito;
              st = 2;
            } 
          else 
            {
              st = 5;
            }
	    }
          break;
	    case 2: {
          if (isSpace(_buf[_indice]) 
              || match(_buf[_indice], '#')) 
            {
              skipSpaces ();
              --_indice; // Si no se retrocede, 
              // al final del bucle se
              // saltara un caracter
            } 
          else if (match(_buf[_indice], '}')) 
            {
              _blks.pop_back ();
              if (--ambito == 0) 
                {
                  st = 0;
                } else {
                  st = 2;
                }
            } 
          else 
            {
              parseToken ();
              if (match(_buf[_indice], '{')) 
                {
                  --_indice; // si no se deja un 
                  // espacio entre el 
                  // token y la llave, 
                  // esta se salta; retroceder
                  // para evitarlo
                }

              if (! hayToken()) 
                {
                  return;
                }
              st = 3;
            }
	    }
          break;
	    case 3: {
          if (isSpace(_buf[_indice]) 
              || match(_buf[_indice], '#')) 
            {
              skipSpaces ();
              --_indice; // Si no se retrocede, 
              // al final del bucle se
              // saltara un caracter
            } 
          else if (match(_buf[_indice], '{')) 
            {
              bloque * blk = _blks.back();
              blk->_subloques.push_back 
                (new bloque (_token));
              _blks.push_back (blk->_subloques.back());
              ++ambito;
              st = 2;
            } 
          else if (match(_buf[_indice], '=')) 
            {
              ++_indice; // Saltar el '='
              skipSpaces ();
              parseValor ();
              if (! hayValor()) 
                {
                  return;
                }
              bloque * blk = _blks.back();
							
              blk->_valores.push_back 
                (new valor (_token, _valor));
							
              // Valores detrás de la coma
              while (match(_buf[_indice], ',')) 
                {

                  ++_indice; // Saltar la coma
                  skipSpaces ();
                  parseValor ();

                  if (! hayValor()) 
                    {
                      return;
                    }

                  blk->_valores.push_back 
                    (new valor (_token, _valor));
                }
              st = 2;
            }
	    }
          break;
	    }
	    ++_indice;
      }
  }
	
  bool config::parseBloque ()
  {
	bool ret = false;
	return ret;
  }
	
  void config::skipSpaces ()
  {

	do 
      {
	    if (_buf[_indice] == '#') 
          {
            do 
              {
                ++_indice;
              } while (_buf[_indice] != '\r' 
                       && _buf[_indice] != '\n');
          } 
	    else 
          {
            do 
              {
                ++_indice;
                if (_buf[_indice] == '\r' 
                    || _buf[_indice] == '\n') 
                  {
                    ++_lineas;
                  }

              } while (_buf[_indice] == ' '
                       || _buf[_indice] == '\t'
                       || _buf[_indice] == '\v'
                       || _buf[_indice] == '\f'
                       || _buf[_indice] == '\r'
                       || _buf[_indice] == '\n');
          }

      } while (_buf[_indice] == '#');
  }
	
  void config::skipComment ()
  {
		
	if (_buf[_indice] == '#') 
      {
	    while (_buf[_indice] != '\n' 
               && _buf[_indice] != '\r') 
          {
            ++_indice;
          }
      }
	++_indice;
  }
	
  void config::skipLinebreak ()
  {
	while (_buf[_indice] != '\r' || _buf[_indice] != '\n') 
      {
	    ++_indice;
      }
  }
	
  void config::parseToken ()
  {
	int i = 0;
		
	if (isalpha(_buf[_indice]) || (_buf[_indice] == '_')) 
      {
	    while (i < MAX_TOKEN_LEN 
               && (isalnum(_buf[_indice]) 
                   || (_buf[_indice] == '_')) ) 
          {
            _token[i++] = _buf[_indice++];
          }
      }
	_token[i] = '\0';
  }
	
  void config::parseValor ()
  {
	int i = 0;
		
	if (_buf[_indice] == '"') 
      {
	    ++_indice; // Saltar las comillas del principio
	    while (!finBuffer() && _buf[_indice] != '"') 
          {
            _valor[i++] = _buf[_indice++];
          }
	    ++_indice; // Saltar las comillas del final
      } 
	else 
      {
	    while (!finBuffer() 
               && !(isSpace(_buf[_indice])) 
               && !match(_buf[_indice], ',') ) 
          {
            _valor[i++] = _buf[_indice++];
          }
      }
	_valor[i] = '\0';
  }

  config::vecbloque_t::iterator 
  config::finBloques ()
  {
	return _bloques.end();
  }

  config::vecvalor_t::iterator
  config::finValores ()
  {
	return (*_bloques.begin())->valores().end();
  }
	
  config::vecbloque_t::iterator 
  config::buscarBloque (std::string nombre_bloque)
  {
	return buscarBloque(nombre_bloque, _bloques);
  }

  config::vecbloque_t::iterator
  config::buscarBloque (std::string ruta, vecbloque_t & blks)
  {
	vecbloque_t::iterator ib = blks.begin();
	std::string pri;

	pri = tomarRuta(ruta);

	if (ruta != pri)
      {
	    for (; ib != blks.end(); ++ib)
          {
            if (str_igual(pri.c_str(), (*ib)->_nombre))
              {
                return buscarBloque(tomarValor(ruta, "/"), (*ib)->subloques());
              }
          }
	    throw sis::ex_nobloque ("El bloque " 
                                + pri 
                                + "buscado no esta en el archivo "
                                "de configuracion.");
      }
	else
      {
	    for (; ib != blks.end(); ++ib)
          {
            if (str_igual(pri.c_str(), (*ib)->_nombre))
              {
                return ib;
              }
          }
	    throw sis::ex_nobloque ("El bloque '" 
                                +  pri 
                                + "' no esta en el archivo "
                                "de configuracion.");
      }

	//
	// Aquí no debe llegar nunca
	//
	return finBloques();
  }

  //
  // Clases publicas internas de config
  //
  config::valor::valor ()
	: nombre (0),
	  val (0)
  {
  }
	
  config::valor::valor (const char * pnombre, 
                        const char * pvalor)
	: nombre (sis::strdup(pnombre)),
	  val (sis::strdup(pvalor))
  {
  }

  config::valor::valor (const config::valor & v)
	: nombre (sis::strdup(v.nombre)),
	  val (sis::strdup(v.val))
  {
  }
	
  config::valor::~valor ()
  {
	delete [] nombre;
	delete [] val;
  }
	
  config::valor & config::valor::operator = (const valor & v)
  {
	delete [] nombre;
	delete [] val;

	nombre = sis::strdup(v.nombre);
	nombre = sis::strdup(v.val);

	return *this;
  }

  config::bloque::bloque ()
	:	_nombre (0)
  {
  }
	
  config::bloque::bloque (const char * nombre)
	:	_nombre (sis::strdup(nombre))
  {
  }
	
  config::bloque::~bloque ()
  {
	delete [] _nombre;
	
	vecvalor_t::iterator itvalor = _valores.begin();
		
	for (; itvalor != _valores.end(); ++itvalor) 
      {
	    delete (*itvalor);
      }
		
	vecbloque_t::iterator itbloque = _subloques.begin();
		
	for (; itbloque != _subloques.end(); ++itbloque) 
      {
	    delete (*itbloque);
      }
		
  }

  std::string 
  config::bloque::buscarValor (std::string val)
  {
	vecvalor_t::iterator iv = _valores.begin();

	for (; iv != _valores.end(); ++iv)
      {
	    if (str_igual(val.c_str(), (*iv)->nombre))
          {
            return (*iv)->val;
          }
      }
    return "";
  }

    
} // end namespace ntp
