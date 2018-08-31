#ifndef __CINT__
#include "IoOperation.hh"
#endif

using namespace std;

TObject* GetObject( string file_name, string obj_name)
{

  TFile* tf = new TFile( file_name.c_str(), "READ"  );

  if( !tf->IsOpen() )
    {
      cerr << "TObject* GetObject( string file_name, string obj_name)" << endl;
      cerr << "\"" << file_name << "\" does not exist" << endl;
      //      exit(-1);
      return new TObject();
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
      return new TObject();
      //      exit(-1);
    }

  TH1::AddDirectory(kFALSE);
  TObject* obj = tf->Get( obj_name.c_str() )->Clone();
  //  tf->Close();
  return obj;
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

vector < double > SplitLine2Double( string line , string delimiter )
{
  vector < string > vwords = SplitLine2String( line, delimiter );

  vector < double > vvalues;
  for( int i=0, itotal=vwords.size(); i<itotal; i++ )
    vvalues.push_back( String2Double( vwords[i] ) );

  return vvalues;
}


vector < string >  SplitLine2String( string line, string delimiter )
{

  vector < string > vwords; 
  SplitLine2String_Internal( line, vwords, delimiter );
  return vwords;
}


void SplitLine2String_Internal( string line, vector < string >& vwords, string delimiter )
{

  // if delimiter is still exist in line, keep splitting!
  if( line.find ( delimiter ) != string::npos )
    {
      string word     = line.substr( 0             , line.find_first_of(delimiter) );
      string residual = line.substr( word.size()+1 , line.size() - word.size()     ) ;
      
      vwords.push_back( word );
      if( residual.size() != 0 )
	SplitLine2String_Internal( residual, vwords, delimiter );
    }
  // if no delimiter is found, this is the lest element. Keep it!
  else
    {
      vwords.push_back( line );
    }
}
