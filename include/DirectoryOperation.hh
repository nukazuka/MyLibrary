#ifndef MYLIB_DIRECTORYOPERATION_HH
#define MYLIB_DIRECTORYOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

/*
  @fn void GetFileNames( string path , vector < string >& vname)
  @param path path to the directory which you want to see
  @param vname name of files are stroed in this
  @param bl_path if true is given, path to files are also stored
  @retval true the directory was found and got name of files successfully
  @retval false the directory was not found or the name of files are not got somehow
  @brief name of all files in the specified directory are stored in vector < string >

 */
bool GetFileNames( string path, vector < string >& vname , bool bl_path=false , string true_suffix = "" );

bool GetFileNames( string path, vector < string >& vname );

bool GetFilePaths( string path, vector < string >& vname );





#endif // MYLIB_DIRECTORYOPERATION_HH
