#ifndef MYLIB_DIRECTORYOPERATION_HH
#define MYLIB_DIRECTORYOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "StringOperation.hh"

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

/*!
  @fn bool CheckSuffix( string name, string true_suffix )
  @param name the name of the file to be checked
  @param true_suffix suffixes to be accepted
  @retval true this file contains one of suffixes
  @retval false this file doesn't
  @brief check if the name of the file contains one of specified suffixes or not
  @details forat of suffixes is like ".dat.data.root"
*/
bool CheckSuffix( string name, string true_suffix );

/*!
  @fn bool GetFileNames( string path, vector < string >& vname , bool bl_path, string true_suffix )
  @param path path to the directory which you want to see
  @param vname name of files are stroed in this
  @param bl_path if true is given, path to files are also stored
  @retval true the directory was found and got name of files successfully
  @retval false the directory was not found or the name of files are not got somehow
  @brief name of all files in the specified directory are stored in vector < string >
  @detail this function is the most prilitive. Use functions below.
 */
bool GetFileNames( string path, vector < string >& vname , bool bl_path=false , string true_suffix = "" );


/*!
  @fn bool GetFileNames( string path, vector < string >& vname, string true_suffix = ""  );
  @brief you can specify a path to the directory, suffixes to be accepted
*/
bool GetFileNames( string path, vector < string >& vname, string true_suffix = ""  );

/*!
  @fn bool GetFileNames( string path, vector < string >& vname );
  @brief you can specify a path to the directory
*/
bool GetFileNames( string path, vector < string >& vname );

/*!
  @fn bool GetFilePaths( string path, vector < string >& vname, string true_suffix = "" );
  @brief paths to the file in a specified directory are stored in vector < string >
  @details you can specify a path to the directory and suffixes to be accepted
*/
bool GetFilePaths( string path, vector < string >& vname, string true_suffix = "" );

/*!
  @fn bool GetFilePaths( string path, vector < string >& vname);
  @brief you can specify a path to the directory
*/
bool GetFilePaths( string path, vector < string >& vname);

#endif // MYLIB_DIRECTORYOPERATION_HH
