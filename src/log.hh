/** 
 * Copyright (c) 2006 by AMPER Sistemas 
 * 
 * Private and Confidential 
 * Information contained in this document is property 
 * of AMPER Sistemas. It is for 
 * the exclusive use of designated employees and  
 * not for distribution without authorization. 
 * 
 * \file log.hpp 
 * \author Manuel Cano Muñoz
 * \date Thu Aug 03 15:41:42 2006
 * 
 * \brief 
 * 
 * 
 */
#ifndef __log_hpp__
#define __log_hpp__

#include <iostream>


#define __MFILE__ __FILE__
#define __MFUNCTION__ __PRETTY_FUNCTION__
#define mcout std::cout
#define mcerr std::cerr
#define mostream std::ostream

#ifdef LOG
#define bfunc() __spc__ spc(__MFUNCTION__);
#define log(x) mcerr << spc << x << std::endl;
#else
#define bfunc()
#define log(x)
#endif

class __spc__
{
	friend mostream & operator << (mostream & o, __spc__ & spc);
public:
	__spc__ (const char * f)
		: _f (f),
		  _l (f)
		{
			mcerr << c << "> "<< f << std::endl;
			spc += 4;
			::memset(c, ' ', spc);
			c[spc] = '\0';
		}

	~__spc__ ()
		{
			if (::strcmp(_f, _l) != 0)
				mcerr << c << "<" << _f << std::endl;
			spc -= 4;
			if (spc)
				::memset(c, ' ', spc);
			c[spc] = '\0';
		}
private:
	static int spc;
	static char c[1024];
	const char * _f;
	const char * _l;
};

mostream & operator << (mostream & o, __spc__ & spc);

#endif
