//#include <spdlog/spdlog.h>
#ifndef PQ_LIBRARY_H
#define PQ_LIBRARY_H
#endif //PQ_LIBRARY_H
#include <exception>

#include <string>
#include <vector>

#include <k.h>

#undef U      // Collision between template types in c++ and this macro u.
#undef R      // Collision between template types in c++ and this macro u.

//List of all PQ setting variables.
extern int savechunksize;


extern "C"
int kstreamread(std::string,std::string);
extern "C"
int kgetschema(K &ms,std::string s);
extern "C"
int kgetfile(K &ms,std::string s);
extern"C"
int kgetfilebycols(K &ms,std::vector<std::string>,std::string s);
extern"C"
int kgetfilebyindicies(K &ms,std::vector<int>,std::string s);
extern"C"
int ksettabletofile(K tab,std::string ms);
