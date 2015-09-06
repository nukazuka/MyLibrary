#include "GetTree.hh"
using namespace std;

TTree* GetTree( string filename, string type)
{

  TFile* tf = new TFile( filename.c_str() );

  if( !tf->IsOpen() )
    {
      
      cerr << "TTree* GetTree( string filename, string type)" << endl;
      cerr << "\"" << filename << "\" does not exist" << endl;
      exit(-1);
    }
  
  const int key_num = tf->GetNkeys();
  bool bl_exist = false;

  for( int i=0; i<key_num; i++)
    {

      string key_name = tf->GetListOfKeys()->At(i)->GetName();
      if( type == key_name )
	{
	  bl_exist = true;
	  break;
	}
    }

  if( !bl_exist )
    {
      cerr << "TDirectoryFile :" << type << " are not found in " << filename << endl;
      exit(-1);
    }

  TDirectoryFile* tdf = (TDirectoryFile*)tf->Get( type.c_str() );

  TTree* tr;
  if( type=="RD" )
    {

      tr = (TTree*)tdf->Get( "RD_event" );
    }
  else if( type=="MC" )
    {

      tr = (TTree*)tdf->Get( "MC" );
    }
  else
    {
      cerr << "TTree* GetTree(string, string )" << endl;
      cerr << "2nd argument: " << type << " does not mach" << endl;
      exit(-1);
    }

  return tr;
}
