#include "library.h"
#include <k.h>
#include <iostream>
int savechunksize=10000;
extern "C"
K setvar(K x,K y)
{
if(-11!=x->t){return krr("argtype");};
std::string ms((char*)x->s);
//Set chunck size when saving.
  if(ms=="savechunksize")
  {
      if(-7!=y->t) {return krr("argtype");};
         savechunksize = y->j;

  }
return (K)0;
}


extern "C"
K getvar(K x)
{
        if(-11!=x->t){return krr("argtype");};
        std::string ms((char*)x->s);
//Get chunck size when saving.
        if(ms=="savechunksize"){return   kj(savechunksize);}
        return (K)0;
}

extern "C"
K getfilebycols(K x,K cols) {
    char *s = x->s;
    if(-11!=x->t){return krr("argtype");};
    if(11!=cols->t){return krr("argtype");};
    K ns = (K) 0;
    std::string ms(s);
    std::string col;
    std::vector<std::string> colnames;
    for(int i=0;i<cols->n;i++) {
        std::string col(kS(cols)[i]);
        colnames.push_back(col);
    }
    try{
    kgetfilebycols(ns,colnames, ms);
    } catch(...)
    {
	    return krr("error");
    }
  return ns;
}

K getfilebyindicies(K x,K indicies) {
   return krr("nyi");

    return (K)0;
}
extern "C"
K getfile(K x) {
    if(-11!=x->t){return krr("argtype");};
   char *s = x->s;
   K ns = (K) 0;
   try{
    std::string ms(s);
        kgetfile(ns, ms);
  }catch(...)
{
 return krr( "error");
}
    return ns;
}
extern "C"
K getschema(K x) {
    if(-11!=x->t){return krr("argtype");}; 
    char* s=x->s;
    K ns=(K)0;
    std::string ms(s);

    try {
       int i = kgetschema(ns,ms);
    }catch(...) {
        krr("cant");
        return K(0);
    }
    return ns;
}


extern "C"
K init(K x) {
    return (K)0;
}

extern "C"
K getproperties(K x) {
    return (K)0;
}

extern"C"
K settabletofile(K file,K tab)
{
    int r=0;
    char* s=file->s;
    std::string ms(s);
    try {
        r = ksettabletofile(tab, ms);
    } catch(...) {
        krr("cantsave");
        return K(0);
    }
    return ki(r);
}

extern"C"
K versioninfo(K a)
{
 K y = ktn(0, 2);
 K x = ktn(KS, 2);
 
 kS(x)[0] = ss((char *) "builddatetime");
 kK(y)[0] = kp(  __TIMESTAMP__  );

 kS(x)[1] = ss((char *) "buildinfo");
 kK(y)[1] = kp( __VERSION__ ); 


return xD(x,y);
}

extern "C"
K streamread(K file,K callback)
{   
    char* s=file->s;
    char* cb=callback->s;
    std::string ms(s);
    std::string cbk(cb);
    kstreamread(ms,cbk);
    return (K)0;
}

extern "C"
K getparquetlib(K a) {
    K y = ktn(0, 11);
    K x = ktn(KS, 11);

    kS(x)[0] = ss((char *) "init");
    kK(y)[0] = dl((V *) init, 1);

    kS(x)[1] = ss((char *) "getproperties");
    kK(y)[1] = dl((V *) getproperties, 1);

    kS(x)[2] = ss((char *) "getschema");
    kK(y)[2] = dl((V *) getschema, 1);

    kS(x)[3] = ss((char *) "getfile");
    kK(y)[3] = dl((V *) getfile, 1);

    kS(x)[4] = ss((char *) "getfilebycols");
    kK(y)[4] = dl((V *) getfilebycols, 2);

    kS(x)[5] = ss((char *) "settabletofile");
    kK(y)[5] = dl((V *) settabletofile, 2);

    kS(x)[6] = ss((char *) "versioninfo");
    kK(y)[6] = dl((V *) versioninfo, 1);

    kS(x)[7] = ss((char *) "getfilebyindicies");
    kK(y)[7] = dl((V *) getfilebyindicies, 2);

    kS(x)[8] = ss((char *) "setvar");
    kK(y)[8] = dl((V *) setvar, 2);

    kS(x)[9] = ss((char *) "getvar");
    kK(y)[9] = dl((V *) getvar, 1);

    kS(x)[10] = ss((char *) "streamread");
    kK(y)[10] = dl((V *) streamread, 2);

    return xD(x, y);
}
