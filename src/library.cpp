#include "library.h"
#include "Kx/k.h"
#include <iostream>


extern "C"
K getfilebycols(K x,K cols) {
    char *s = x->s;
    K ns = (K) 0;
    std::string ms(s);
    std::string col;
    std::vector<std::string> colnames;
    for(int i=0;i<cols->n;i++) {
        std::string col(kS(cols)[i]);
        colnames.push_back(col);
    }
    kgetfilebycols(ns,colnames, ms);

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
K getparquetlib(K a) {
    K y = ktn(0, 8);
    K x = ktn(KS, 8);

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

    return xD(x, y);
}
