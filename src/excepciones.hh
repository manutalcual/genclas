//
//
//

#ifndef __excepciones_h__
#define __excepciones_h__

namespace sis
{

    class ex
    {
    public:
	ex ();
	ex (const char * str);
	ex (const ex & e);
	virtual ~ex ();
	virtual operator const char * ();
    private:
    protected:
	char * _str;
    };

    class ex_inval_parm : public ex
    {
    public:
	ex_inval_parm (const char * str)
	    : ex (str)
	    {
	    }
    private:
    };

    class ex_rango : public ex
    {
    public:
	ex_rango (const char * str)
	    : ex (str)
	    {
	    }
    private:
    };

    class ex_nofile : public ex
    {
    public:
	ex_nofile (const char * str)
	    : ex (str)
	    {
	    }
    private:
    };

    class ex_noconf : public ex
    {
    public:
	ex_noconf (const char * str)
	    : ex (str)
	    {
	    }
    private:
	
    };

    class ex_nocapt : public ex
    {
    public:
	ex_nocapt (const char * str)
	    : ex (str)
	    {
	    }
    private:
    };


}

#endif // __excepciones_h__
