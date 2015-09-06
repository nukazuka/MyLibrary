#ifndef MYLIB_IOOPERATION_HH
#define MYLIB_IOOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

using namespace std;

/*! get root object*/
TObject* GetObject( string file_name, string obj_name);

/*! get root object in TDirectoryFile */
TObject* GetObject( string file_name, string dir_name, string obj_name);

/*! get TTree */
TTree* GetTree( string file_name , string tr_name );

/*! get TTree in TDirectoryFile */
TTree* GetTree( string file_name , string dir_name, string tr_name );

#endif
