#ifndef MYLIB_IOOPERATION_HH
#define MYLIB_IOOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

using namespace std;

/*!
  @fn TObject* GetObject( string file_name, string obj_name)
  @param
  @return
  @brief get root object
 */
TObject* GetObject( string file_name, string obj_name);

/*!
  @fn TObject* GetObject( string file_name, string dir_name, string obj_name)
  @param
  @return
  @brief get root object in TDirectoryFile
 */
TObject* GetObject( string file_name, string dir_name, string obj_name);

/*!
  @fn TTree* GetTree( string file_name , string tr_name )
  @param
  @return
  @brief get TTree
 */
TTree* GetTree( string file_name , string tr_name );

/*!
  @fn TTree* GetTree( string file_name , string dir_name, string tr_name )
  @param
  @return
  @brief get TTree in TDirectoryFile
 */
TTree* GetTree( string file_name , string dir_name, string tr_name );

#ifdef __CINT__
#include "../src/IoOperation.cc"
#endif

#endif
