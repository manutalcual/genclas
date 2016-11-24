//
// Clase: parser Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Wed Mar 15 16:29:27 2006
// Time-stamp: <11-ago-2006 14:43:25 mcano>
//
//
// Includes
//
#include "parser.hh"

namespace sis {


    parser::parser (std::string fname, std::string clase,
                    sis::config::bloque & bl)
        : _bloque (bl),
          _ok (false),
          _str (0),
          _i (0),
          _size (0),
          _clase (clase)
    {
        file f (fname.c_str());

        _str = f.cargar();
        _size = f.size();
        log("El tamano del archivo es de " << _size << " bytes.");

        _ok = analiza();

        log("Resultado:");
        log("Se han recorrido " << _i << " bytes.");
        log(_buf);
        log("==========================================");
    }

    parser::~parser ()
    {
        delete [] _str;
    }

    parser::operator bool ()
    {
        return _ok;
    }

    std::string & parser::resultado ()
    {
        return _buf;
    }

    bool parser::analiza ()
    {
        log("analiza()");
        do
        {
            switch (_str[_i])
            {
            case '$':
                _buf += escapa(_i);
                break;
            case '\\':
                ++_i;
                _buf += escapaComando(&_bloque, _i);
                break;
            default:
                _buf += _str[_i];
                break;
            }
            ++_i;
        }
        while (_str[_i] != '\0');

        return true;
    }

    std::string parser::escapa (int & i)
    {
        log("escapa()");
        std::string ret;
        std::string word;

        ++_i; // Saltar el '$'
        if (i < _size && _str[i] == '{')
        {
            ++i; // Saltar el '{'
            while (i < _size && _str[i] != '}')
            {
                word += _str[i];
                ++i;
            }
            // En este bucle se salta automáticamente el '}'
        }
        else
        {
            while (i < _size && ::isalnum(_str[i]) || (_str[i] == '_'))
            {
                word += _str[i];
                ++i;
            }
            --i; // Hemos saltado una posición en el bucle, la recuperamos
        }

        log("Variable a buscar: " << word);
        if (word == "usuario")
        {
            ret = sis::env::user();
        }
        else if (word == "fecha")
        {
            ret = sis::date();
        }
        else if (word == "clase")
        {
            ret = _clase;
        }
        else
        {
            ret = sis::env::get(word);
            if (ret == "")
            {
                ret = _bloque.buscarValor(word);
            }
        }
        log("Cadena escapada: '" << ret << "'");
        return ret;
    }

    std::string parser::skipComando (int & i)
    {
        std::string com ("");
        int llaves = 1; // Llaves de apertura

        while (i < _size && _str[i] != '{')
        {
            com += _str[i];
            ++i;
        }
        com += _str[i];
        ++i;

        while (i < _size && llaves)
        {
            if (_str[i] == '}') 
            {
                // Con la llave de cierre,
                // decrementamos la cuenta de llaves :)
                --llaves;
            }
            else if (_str[i] == '{')
            {  
                // Con la llave de apertura,
                // incrementamos la cuenta de
                // llaves :(
                ++llaves;
            }
            com += _str[i];
            ++i;
        }

        return com;
    }

    std::string parser::escapaComando (sis::config::bloque * blk, int & i)
    {
        log("escapaComando()");
        std::string ret;
        std::string word;
        std::string res;

        if (i < _size && _str[i] != '\\')
        {
            while (i < _size && _str[i] != ' ')
            {
                word += _str[i];
                ++i;
            }

            if (word == "for")
            {
                ++i; // Saltar espacio en blanco
                ret = parseComando(i);
                log("For: " << ret);
                res += comandoFor(blk, ret, i);
            }
            else if (word == "do")
            {
                ++i; // Saltar espacio en blanco
                ret = parseComando(i);
                log("Do: " << ret);
                res += comandoDo(blk, com::factoria(ret), i);
            }
            else if (word == "while")
            {
                ++i; // Saltar espacio en blanco
                ret = parseComando(i);
                log("While: " << ret);
                res += comandoFor(blk, ret, i);
            }
            else
            {
                ++i; // Saltar espacio en blanco
                ret = parseComando(i);
                log("Do: '" << ret << "'");

                std::cerr << "Error: comando " << word 
                          << " no implementado." << std::endl;
                std::string com;

                com = skipComando(i);

                std::cerr << "El comando es el siguiente: " << std::endl;
                std::cerr << com << std::endl;

                res += "\n/*\n * Error: comando '";
                res += word;
                res += "' desconocido.\n";
                res += " *\n";
                res += " * Texto del comando.\n";
                res += " *\n";
                res += com;
                res += "\n */\n";
            }
        }
        else
        {
            res += '\\';
        }

        return res;
    }

    std::string parser::parseComando (int & i)
    {
        std::string nom;

        while (i < _size && ::isalnum(_str[i]) || _str[i] == '_')
        {
            nom += _str[i];
            ++i;
        }

        return nom;
    }

    std::string parser::comandoFor (sis::config::bloque * blk,
                                    std::string nom, int & i)
    {
        log("Comando FOR.");
        int pos = 0;
        int end = 0;
        bool encontrado = false; // Si el nombre del comando esta en
        // el bloque
        std::string ret;
        sis::config::vecbloque_t::iterator ib = blk->subloques().begin();
        sis::config::vecbloque_t::iterator ie = blk->subloques().end();

        while (i < _size && _str[i] != '{')
            ++i;

        // Guardamos la posicion del inicio del bloque, depues de
        // saltar el '{'
        pos = ++i;

        for (; ib != ie; ++ib)
        {
            log("Bloque: " << (*ib)->nombre());
            //
            // Poner todos los valores que tengan el nombre del bloque
            // que estamos tratando (p.e.  parametros, funciones,
            // etc.) todos ellos especificados en el bloque del
            // archivo .conf
            //
            if ((*ib)->nombre() == nom)
            {
                encontrado = true;
                break;
            }
        }

        //
        // Tratar el comando desconocido
        //
        if (! encontrado)
        {
            int llaves = 1; // Llaves de apertura

            while (i < _size && llaves)
            {
                if (_str[i] == '}') 
                {
                    // Con la llave de cierre,
                    // decrementamos la cuenta de llaves :)
                    --llaves;
                }
                else if (_str[i] == '{')
                {  
                    // Con la llave de apertura,
                    // incrementamos la cuenta de
                    // llaves :(
                    ++llaves;
                }
                ++i;
            }
            return "";
        }

        log("Bloque encontrado: " << (*ib)->nombre());
        sis::config::vecbloque_t::iterator sib = (*ib)->subloques().begin();
        sis::config::vecbloque_t::iterator sie = (*ib)->subloques().end();

        if (sib == sie)
        {
            int llaves = 1;
            log("El bloque esta vacio.");
            while (i < _size && llaves)
            {
                if (_str[i] == '}') 
                {
                    // Con la llave de cierre,
                    // decrementamos la cuenta de llaves :)
                    --llaves;
                }
                else if (_str[i] == '{')
                {  
                    // Con la llave de apertura,
                    // incrementamos la cuenta de
                    // llaves :(
                    ++llaves;
                }
                ++i;
            }
            return "";
        }

        for (; sib != sie; ++sib)
        {
            pos = i;
            log("Sub bloque: '" << (*sib)->nombre() << "'.");
            while (i < _size && _str[pos] != '}')
            {
                // Poner valor
                if (_str[pos] == '%')
                {
                    ++pos; // Skip '%'
                    if (_str[pos] == '.')
                    {
                        std::string word;
                        ++pos; // Skip '.'
                        word = parseComando(pos);
                        std::string val;

                        if (word != "")
                        {
                            val = (*sib)->buscarValor(word);
                            if (val != "")
                            {
                                ret += val;
                            }
                        }
                    }
                    else if (_str[pos] == '?')
                    {
                        log("Interrogante.");
                        std::string word;
                        ++pos; // Skip '?'
                        word = parseComando(pos);
                        log("Comando: '" << word << "'.");
                        if (word == "last")
                        {
                            if (sib != (sie - 1))
                            {
                                log("\tfin de bloque.");
                                ++pos; // Skip '{'
                                while (_str[pos] != '}')
                                    ret += _str[pos++];
                            }
                            else
                            {
                                log("no es fin de bloque.");
                                while (_str[pos] != '}')
                                    ++pos;
                            }
                        }
                        else
                        {
                            while (_str[pos] != '}')
                                ret += _str[pos++];
                        }
                    }
                    else
                    {
                        ret += (*sib)->nombre();
                    }
                    --pos;
                }
                // Los comandos se pueden anidar
                else if (_str[pos] == '\\')
                {
                    ++pos; // Saltar el '\'
                    ret += escapaComando(*sib, pos);
                    --pos;
                }
                // Y se pueden poner variables de entorno dentro
                // de los bloques
                else if (_str[pos] == '$')
                {
                    ret += escapa(pos);
                    --pos;
                }
                // Lo demas lo copiamos verbatim
                else
                {
                    ret += _str[pos];
                }
                ++pos;
            }
        }

        log("Saliendo del bloque FOR.");
        return ret;
    }

    std::string parser::comandoDo (sis::config::bloque * blk,
                                   IComando * pcom, int & pos)
    {
        log("comandoDo()");
        IComando & com = *pcom; // Para usar la sintaxis de operadores
        int end = 0;
        bool encontrado = false; // Si el nombre del comando esta en
        // el bloque
        std::string ret;

        while (pos < _size && _str[pos] != '{')
            ++pos;

        // Saltar el '{'
        ++pos;

        while (pos < _size && _str[pos] != '}')
        {
            // Los comandos se pueden anidar
            if (_str[pos] == '\\')
            {
                ++pos; // Saltar el '\'
                ret += escapaComando(blk, pos);
            }
            // Y se pueden poner variables de entorno dentro
            // de los bloques
            else if (_str[pos] == '$')
            {
                std::string es;
                com << escapa(pos);
            }
            // Lo demas lo copiamos verbatim
            else
            {
                com << _str[pos];
            }
            ++pos;
        }
        ret += com.as_string();
        delete pcom;
        pcom = NULL;

        return ret;
    }

} // end namespace sis


