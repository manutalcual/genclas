/** 
 * Copyright (c) 2006 by AMPER Sistemas 
 * 
 * Private and Confidential 
 * Information contained in this document is property 
 * of AMPER Sistemas. It is for 
 * the exclusive use of designated employees and  
 * not for distribution without authorization. 
 * 
 * \file log.cpp 
 * \author Manuel Cano Muñoz
 * \date Thu Aug 03 15:41:42 2006
 * 
 * \brief 
 * 
 * 
 */

#include "log.hh"


int __spc__::spc = 0;
char __spc__::c[1024];


mostream & operator << (mostream & o, __spc__ & spc)
{
	o << spc.c;

	return o;
}
