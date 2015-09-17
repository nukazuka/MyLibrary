#ifndef __CINT__
#include "StringOperation.hh"
#endif

using namespace std;

string GetBaseName( string path )
{

  string rtn = "";
  if( path.find(".") == string::npos )
    rtn = path;
  else
    rtn = path.substr( 0, path.find_last_of(".") );
  return  rtn;
}

string GetSuffix( string path )
{

  string rtn = "";
  if( path.find(".") == string::npos )
    rtn = path;
  else
    rtn = path.substr( path.find_last_of(".")+1, path.size() - path.find_last_of(".") );

  return rtn;
}

string GetFileName( string path )
{

  string rtn = "";
  if( path.find("/") == string::npos )
    rtn = path;
  else
    rtn = path.substr( path.find_last_of("/")+1, path.size() - path.find_last_of("/") );

  return rtn;
}

string GetPathToFile( string path )
{
  string rtn = "";
  if( path.find("/") == string::npos )
    rtn = path;
  else
    rtn = path.substr( 0, path.find_last_of("/") );

  return rtn;
}

string Replace( string word, string old_key, string new_key )
{

  string rtn = word;

  int pos = 0;
  int length = old_key.length();

  for( unsigned int i=0; i<rtn.length(); i++, pos++ )
    {

      if( pos > (int)rtn.length() )
	break;

      string target = rtn.substr( pos , length );

      if( target == old_key )
	{

	  rtn.replace( pos, length, new_key );
	  pos += new_key.size();
	}
    }

  return rtn;
}


string Replace4Cut( string cut )
{

  string rtn = cut;

  // White space
  rtn = Replace( rtn, " " , "_" );

  // Comparison oerators
  rtn = Replace( rtn, "==", "_eq_" );
  rtn = Replace( rtn, ">" , "_gt_" );
  rtn = Replace( rtn, ">=", "_ge_" );
  rtn = Replace( rtn, "<" , "_lt_" );
  rtn = Replace( rtn, "<=", "_le_" );
  rtn = Replace( rtn, "!=", "_ne_" );
  rtn = Replace( rtn, "&&", "_and_" );
  rtn = Replace( rtn, "||", "_or_" );
  rtn = Replace( rtn, "!", "_not_" );

  // Arithmetic operators
  rtn = Replace( rtn, "+", "_plus_" );
  rtn = Replace( rtn, "*", "_mul_" );
  rtn = Replace( rtn, "/", "_dev_" );


  // Other operators
  rtn = Replace( rtn, "(" , "_" );
  rtn = Replace( rtn, ")" , "_" );
  rtn = Replace( rtn, "[" , "_" );
  rtn = Replace( rtn, "]" , "_" );

  // Correction for result directory
  rtn = Replace( rtn, "result_dev_", "result/" );

  return rtn;

}

string Subtraction( string s1, string s2 )
{

  istringstream is1(s1);
  istringstream is2(s2);

  int num1, num2;
  is1 >> num1;
  is2 >> num2;
  int result = num1 - num2;

  stringstream ssrtn;
  ssrtn << result;
  return ssrtn.str();
}

int String2Int( string st )
{

  istringstream iss(st);
  int num;
  iss >> num;

  return num;
}
