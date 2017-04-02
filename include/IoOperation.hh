#ifndef MYLIB_IOOPERATION_HH
#define MYLIB_IOOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "StringOperation.hh"

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

/*!
  @fn vector < double > SplitLine2Double( string line , string delimiter )
  @brief split line with delimiter and stre in vector < double >
*/
vector < double > SplitLine2Double( string line , string delimiter );

/*!
  @fn void SplitLine2String( string line, string delimiter )
  @brief split line with delimiter and store in vector < string >
*/
vector < string > SplitLine2String( string line, string delimiter );

/*!
  @fn void SplitLine2String_Internal( string line, vector < string >& vwords, string delimiter );
  @brief this is for SplitLine2String. Users don't need to use it.
*/
void SplitLine2String_Internal( string line, vector < string >& vwords, string delimiter );

#ifdef __CINT__
#include "../src/IoOperation.cc"
#endif

#endif
