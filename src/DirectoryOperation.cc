#ifndef __CINT__
#include "DirectoryOperation.hh"
#endif // __CINT__

#ifdef __CINT__
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
//#include "StringOperation.cc" // 
#endif

using namespace std;

bool CheckSuffix( string name, string true_suffix )
{
  
  // get the suffix of given file
  string suffix = GetSuffix( name );

  // if the suffix is not in ture suffix, return false
  if( true_suffix.find( suffix ) == string::npos )
    return false;

  return true;
}

bool GetFileNames( string path, vector < string >& vname , bool bl_path, string true_suffix )
{

  // open the directory
  DIR* dp = opendir( path.c_str() );
  
  // if specified directory is not found, return false
  if( dp == NULL)
    return false;
      
  struct dirent* dent;

  // loop over dirent structures until NULL
  do
    {
      
      dent = readdir( dp );
      
      if( dent != NULL )
	{
	  
	  // get the name of the file
	  string name = dent->d_name;

	  if( name == "." || name == ".." )
	    continue;

	  // if suffix is specified AND
	  // this files is not the case, skip this
	  if( true_suffix != "" )
	    if( CheckSuffix( name, true_suffix ) == false )
	      continue;
	  
	  // check if path to this file should be stoed or not
	  // and store name of this file (or path to this file)
	  if( bl_path == true )
	    {

	      if( path.substr( path.size()-1, path.size() ) == "/" )
		vname.push_back( path + name );
	      else
		vname.push_back( path + "/" + name );

	    }
	  else
	    {
	      vname.push_back( name );
	    }
	}
    } 
  while(dent!=NULL);
  
  // close the directory
  closedir(dp);

  // sort stored names
  sort( vname.begin() , vname.end() );
  return true;
}

bool GetFileNames( string path, vector < string >& vname , string true_suffix )
{
  return GetFileNames( path, vname, false, true_suffix );
}


bool GetFileNames( string path, vector < string >& vname )
{
  return GetFileNames( path, vname, false, "" );
}

bool GetFilePaths( string path, vector < string >& vname, string true_suffix )
{
  return GetFileNames( path, vname, true, true_suffix );
}

bool GetFilePaths( string path, vector < string >& vname )
{
  return GetFileNames( path, vname, true, "" );
}

