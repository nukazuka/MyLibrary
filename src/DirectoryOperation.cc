#ifndef __CINT__
#include "DirectoryOperation.hh"
#endif // __CINT__

#ifdef __CINT__
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#endif

using namespace std;

bool GetFileNames( string path, vector < string >& vname , bool bl_path, string true_suffix )
{

  DIR* dp = opendir( path.c_str() );
  if( dp == NULL)
    {
      return false;
    }
  else
    {
      
      struct dirent* dent;
      
      do
	{

	  dent = readdir( dp );

	  if( dent != NULL )
	    {

	      string name = dent->d_name;
	      if( bl_path == true )
		vname.push_back( path + name );
	      else
		vname.push_back( name );
	    }
	} 
      while(dent!=NULL);

      closedir(dp);
    }
  sort( vname.begin() , vname.end() );
  return true;
}

bool GetFileNames( string path, vector < string >& vname )
{
  return GetFileNames( path, vname, false );
}

bool GetFilePaths( string path, vector < string >& vname )
{
  return GetFileNames( path, vname, true );
}

