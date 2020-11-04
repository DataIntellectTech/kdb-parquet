#include "library.h"
#include "Kx/k.h"
#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}
extern "C"
K khello(K x) {
    std::cout << "Hello, World!\n" <<  (x->s) <<std::endl;
    char* s=x->s;
    std::string ms=s;

    return (K)0;
}

extern "C"
K getfilebycols(K x,K cols) {
    char *s = x->s;
    K ns = (K) 0;
    std::string ms(s);
    std::string col;
    std::vector<std::string> colnames;
    for(int i=0;i<cols->n;i++) {
        std::string col(kS(cols)[i]);
        std::cout << col<< std::endl;
        colnames.push_back(col);
    }
    kgetfilebycols(ns,colnames, ms);

  return ns;
}
extern "C"
K getfile(K x) {
    char *s = x->s;
    K ns = (K) 0;
    std::string ms(s);
        kgetfile(ns, ms);

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

extern"C"
K settabletofile(K file,K tab)
{   char* s=file->s;
    std::string ms(s);
    int r=ksettabletofile(tab,ms);
    return ki(r);
}
extern "C"
K getparquetlib(K x) {
    K y = ktn(0, 6);
    x = ktn(KS, 6);

    kS(x)[0] = ss((char *) "init");
    kK(y)[0] = dl((V *) init, 1);

    kS(x)[1] = ss((char *) "khello");
    kK(y)[1] = dl((V *) khello, 1);

    kS(x)[2] = ss((char *) "getschema");
    kK(y)[2] = dl((V *) getschema, 1);

    kS(x)[3] = ss((char *) "getfile");
    kK(y)[3] = dl((V *) getfile, 1);

    kS(x)[4] = ss((char *) "getfilebycols");
    kK(y)[4] = dl((V *) getfilebycols, 2);

    kS(x)[5] = ss((char *) "settabletofile");
    kK(y)[5] = dl((V *) settabletofile, 2);

    return xD(x, y);
}