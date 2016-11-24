//
// Programa: genclas Copyright (c) 2006 Dia%
// Autor: Manuel Cano Muñoz
// Fecha: Wed Mar 15 12:01:45 2006
// Time-stamp: <11-ago-2006 12:33:09 mcano>
//
// Includes
//
#include "main.hh"


#ifdef NDEBUG
std::string RUTA = sis::env::get("HOME");
#else
std::string RUTA = "..";
#endif

const std::string CONF_NAME = "genclas.conf";


int main (int argc, char ** argv)
{
    try
    {
#ifdef NDEBUG
		RUTA += "/etc/genclas/";
#else
		RUTA += "/etc/";
#endif

		log("La ruta construida es: " << RUTA);

		sis::options_parser opts (argc, argv);

		if (opts["help"] != "")
		{
			uso (argv[0]);
			::exit (0);
		}

		opts.add_mandatory ("tipo-clase");
		opts.add_mandatory ("clase");

		if (! opts)
		{
			sis::mandatory_t::iterator iob = opts.parametros_faltan().begin();
			sis::mandatory_t::iterator ioe = opts.parametros_faltan().end();

			std::cerr << "Faltan parámetros: " << std::endl;

			for (; iob != ioe; ++iob)
			{
				std::cerr << "\t" << *iob << std::endl;
			}
			uso (argv[0]);
			::exit (1);
		}

		std::string conf_name;

		if (opts["conf-dir"] != "")
		{
			RUTA = opts["conf-dir"] + "/";
		}

		if (opts["conf-file"] != "")
		{
			conf_name = opts["conf-file"];
		}
		else
		{
			conf_name = RUTA;
			conf_name += CONF_NAME;
		}

		log("Archivo de configuración: " << conf_name);
		sis::config conf (conf_name);
		std::string tipo (opts["tipo-clase"]);
		log("Buscando bloque.");
		sis::config::vecbloque_t::iterator ibb = conf.buscarBloque(
			"principal/" + tipo);

		if (ibb == conf.finBloques())
		{
			log("Se ha llegado al final de los bloques y no se ha encontrado "
				<< "el que se buscaba.");
			throw sis::ex_nobloque("El bloque de plantillas no ha sido "
								   "encontrado");
		}

		std::string fnom;
		fnom = RUTA;
		fnom += (*ibb)->_nombre;
		fnom += ".plantilla";

		log("Archivo de plantilla: " << fnom);
		sis::parser p (fnom, opts["clase"],  *(*ibb));

		if (p)
		{
			log("Obteniendo resultado.");
			std::string res = p.resultado();
			log("Imprimimiendo resultado.");
			std::cout << res << std::endl;
		}
    }
    catch (sis::ex & e)
    {
		std::cerr << "Excepción: " << e << std::endl;
    }
    catch (const char * ex)
    {
		std::cerr << "Excepcion: " << ex << std::endl;
    }
    catch (...)
    {
		std::cerr << "Excepción: desconocida." << std::endl;
    }

    return 0;
}


void uso (const char * prg)
{
    std::cout << prg << " [opciones]"<< std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "\t--help" << std::endl;
    std::cout << "\t--conf-file=<archivo>" << std::endl;
    std::cout << "\t--conf-dir=<directorio>" << std::endl;
    std::cout << "\t--tipo-clase=<valor> "
		"(Especificar un tipo del archivo genclas.conf)" 
			  << std::endl;
    std::cout << "\t--clase=<nombre>" << std::endl;
}
