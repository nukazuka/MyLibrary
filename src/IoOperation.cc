#include "IoOperation.hh"

using namespace std;

TObject* GetObject( string file_name, string obj_name)
{

  TFile* tf = new TFile( file_name.c_str() );

  if( !tf->IsOpen() )
    {
      cerr << "TObject* GetObject( string file_name, string obj_name)" << endl;
      cerr << "\"" << file_name << "\" does not exist" << endl;
      exit(-1);
    }
  
  bool bl_exist = false;

  for( int i=0; i<tf->GetNkeys(); i++ )
    {
      
      if( tf->GetListOfKeys()->At(i)->GetName() == obj_name )
	{
	  bl_exist = true;
	  break;
	}
    }

  if( !bl_exist )
    {
      cerr << "TObject* GetObject( string file_name, string dir_name, string obj_name)" << endl;
      cerr << "TObj :" << obj_name << " are not found in " << file_name << endl;
      tf->ls();
      exit(-1);
    }

  
  return (TObject*)tf->Get( obj_name.c_str() );
}

TObject* GetObject( string file_name, string dir_name, string obj_name)
{

  TFile* tf = new TFile( file_name.c_str() );

  if( !tf->IsOpen() )
    {
      cerr << "TObject* GetObject( string file_name, string dir_name, string obj_name)" << endl;
      cerr << "\"" << file_name << "\" does not exist" << endl;
      exit(-1);
    }
  
  bool bl_exist = false;

  for( int i=0; i<tf->GetNkeys(); i++)
    {

      string dir = tf->GetListOfKeys()->At(i)->GetName();
      if( dir == dir_name )
	{
	  bl_exist = true;
	  break;
	}
    }

  if( !bl_exist )
    {
      cerr << "TObject* GetObject( string file_name, string dir_name, string obj_name)" << endl;
      cerr << "TDirectoryFile :" << dir_name << " are not found in " << file_name << endl;
      tf->ls();
      exit(-1);
    }

  TDirectoryFile* tdf = (TDirectoryFile*)tf->Get( dir_name.c_str() );
  bl_exist = false;
  for( int i=0; i<tdf->GetNkeys(); i++ )
    {
      
      if( tdf->GetListOfKeys()->At(i)->GetName() == obj_name )
	{
	  bl_exist = true;
	  break;
	}
    }

  if( !bl_exist )
    {
      cerr << "TObject* GetObject( string file_name, string dir_name, string obj_name)" << endl;
      cerr << "TObj :" << obj_name << " are not found in " << file_name << endl;
      tdf->ls();
      exit(-1);
    }

  
  return (TObject*)tdf->Get( obj_name.c_str() );
}

TTree* GetTree( string file_name , string tr_name )
{
  return (TTree*)GetObject(file_name, tr_name);
}

TTree* GetTree( string file_name , string dir_name, string tr_name )
{
  return (TTree*)GetObject( file_name, dir_name, tr_name );
}
