/**
 * Copyright (c) Amper Sistemas 2006
 * \file Recorder.hh
 * \author manuel
 * \date Sat Aug 12 21:39:50 2006
 * 
 * \brief Class Recorder
 *
 * TODOC
 *
 */

#ifndef __RECORDER_H__
#define __RECORDER_H__

#include <string>
#include <time.h>
#include "bencode.hh"
#include "InterObject.hh"


#include "string" // Esto no es time.h
	// Esto sigue sin ser time 

#include "time.h" // poner esto en time



namespace dcn {

    /** 
     * \brief Class Recorder. TODOC
     *
     * TODOC
     *
     */
    class Recorder : public IRecord, public InterObjectClient
    {
    public:
         
        /**
         * \brief Func. Recorder TODOC
         * 
	 * \param interface const char * TODOC 
         */
	Recorder (const char * interface);
        
         
        /**
         * \brief Func. Recorder TODOC
         */
	~Recorder ();
        
         
        /**
         * \brief Func. Record TODOC
         * 
         *
         * \return int 
         */
	int Record ();
         
        /**
         * \brief Func. Prueba TODOC
         * 
         *
         * \return 
         */
	Prueba ();
         
        /**
         * \brief Func. GetSpeed TODOC
         * 
	 * \param speed int & TODOC 
	 * \param timestamp time_t TODOC 
         *
         * \return int 
         */
	int GetSpeed (int & speed, time_t timestamp);
        
    protected:
    private:
    };

} // end namespace dcn

#endif
