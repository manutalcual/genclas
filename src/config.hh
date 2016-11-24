//
//
//
#include <ctype.h>
#include <string.h>
#include <vector>


#ifndef __config_h__
#define __config_h__

#include "excepciones.hh"
#include "file.hh"
#include "utils.hh"


namespace sis {

#   define MAX_TOKEN_LEN 64
#   define MAX_VALUE_LEN 1023

  using std::vector;

  class ex_nobloque : public ex
  {
  public:
	ex_nobloque (std::string str);
	ex_nobloque (const ex_nobloque & e);
	operator const char * ();
  private:
	std::string _er;
  };

  class config
  {
  public:
	class valor
	{
	public:
      char * nombre;
      char * val;
      valor ();
      valor (const char * nombre, const char * valor);
      valor (const valor & v);
      ~valor ();
      valor & operator = (const valor & v);
	};

	typedef std::vector<sis::config::valor *> vecvalor_t;

	class bloque
	{
	public:
      char * _nombre;
      vecvalor_t _valores;
      vector<bloque *> _subloques;
      bloque ();
      bloque (const char * nombre);
      ~bloque ();
      const char * nombre () { return _nombre; };
      vector<bloque *> & subloques () { return _subloques; }
      vecvalor_t & valores () { return _valores; }
      std::string buscarValor (std::string val);
	};

	typedef std::vector<sis::config::bloque *> vecbloque_t;
	
	config (std::string nombre);
	~config ();
	void parse ();
    vecbloque_t &  bloques () { return _bloques; }
	vecbloque_t::iterator finBloques ();
	vecvalor_t::iterator finValores ();

	vecbloque_t::iterator buscarBloque (std::string nombre);
  protected:
  private:
	std::string _nombre;
	int _num_buf;
	int _len_buf;
	char * _buf;
	int _indice;
	char _token[MAX_TOKEN_LEN + 1];
	char _valor[MAX_VALUE_LEN + 1];
	int _lineas;
	vecbloque_t _bloques;
	vecbloque_t _blks;
	
	bool parseBloque ();
	
	void parseToken ();
	void parseValor ();
		
	bool finBuffer () { return (_indice >= _len_buf); }
		
	bool hayToken () { return ::strlen(_token); }
	void clearToken () { _token[0] = '\0'; }
	void agregarBloque () { _bloques.push_back (new bloque (_token)); }
		
	bool hayValor () { return ::strlen(_valor); }
	void clearValor () { _valor[0] = '\0'; }
		
	bool match (char ch1, char ch2) { return (ch1 == ch2); }
	bool isSpace (char ch) 
    {
      return (ch == ' '
              || ch == '\t'
              || ch == '\v'
              || ch == '\f'
              || ch == '\r'
              || ch == '\n');
    }

	void skipSpaces ();
	void skipComment ();
	void skipLinebreak ();

	vecbloque_t::iterator buscarBloque (std::string nombre_bloque,
                                        vecbloque_t & blks);
  };

    
	
} // end namespace sis

#endif // __config_h__
