/**
 * Copyright (c) Amper Sistemas 2006
 * \file Recorder.cc
 * \author manuel
 * \date Sat Aug 12 21:39:50 2006
 * 
 */

#include "Recorder.hh"

namespace dcn {

    
    Recorder::Recorder (const char * interface)
        : InterObjectClient (interface)
    {
    }
    
    
    Recorder::~Recorder ()
    {
    }
    
    
    int Recorder::Record ()
    {
	
	dcn::bencode data;
	int retvar = 0;
	
	
	send_call (data.str());

	m_stream >> retvar;

	if (retvar == true)
        {
            
        }

	return retvar;
	 
	
    } 
    
    Recorder::Prueba ()
    {
	
	
	send_call ();
	 
    } 
    
    int Recorder::GetSpeed (int & speed,  time_t timestamp )
    {
	
	dcn::bencode data;
	int retvar = 0;
	
	data << speed;
	data << timestamp;
	
	send_call (data.str());

	m_stream >> retvar;

	if (retvar == true)
        {
            m_stream >> speed;
            m_stream >> timestamp;
            
        }

	return retvar;
	 
	
    } 
    
} // end namespace dcn

