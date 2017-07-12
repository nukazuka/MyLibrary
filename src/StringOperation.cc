#ifndef __CINT__
#include "StringOperation.hh"
#endif

using namespace std;

int CountCharactor( string target , string key )
{

  int counter = 0;
  for( int i=0; i<target.size() - key.size(); i++ )
    {
      string part = target.substr( i , key.size() );
      if( part == key )
	counter++;
    }

  return counter;      
}

string Double2String( double num , int precision )
{
  stringstream ss;
  ss << setprecision( precision ) << num;
  return ss.str();
}


string GetBaseName( string path )
{

  string file_name = GetFileName( path );
  string file_suffix = GetSuffix(path);
  string rtn = Replace( file_name, file_suffix, "" );
  return  rtn;
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
  if( path.find("/") != string::npos )
    rtn = path.substr( 0, path.find_last_of("/") );

  return rtn;
}


string GetRepeatedWords( string word, int num )
{

  string rtn = "";
  for( int i=0; i<num; i++)
    rtn += word;
  //  string rtn( num , word );
  return rtn;
}


string GetSuffix( string path )
{

  string rtn = "";
  if( path.find(".") == string::npos )
    rtn = path;
  else
    rtn = path.substr( path.find_last_of("."), path.size() - path.find_last_of(".")+1 );

  return rtn;
}

string InsertAtFirstOf( string st , string delimiter , string st_added )
{
  int first_point = st.find_first_of( delimiter );
  string rtn = st.substr( 0,  first_point )
    + st_added
    + st.substr( first_point , st.size() - first_point );
  return rtn;
}

string InsertAtLastOf( string st , string delimiter , string st_added )
{
  int last_point = st.find_last_of( delimiter );
  string rtn = st.substr( 0,  last_point )
    + st_added
    + st.substr( last_point , st.size() - last_point );
  return rtn;
}

string Int2String( int num )
{

  stringstream ss;
  ss << num;
  return ss.str();
}

bool IsNumber( string st )
{

  string::const_iterator it = st.begin();
  while( it != st.end() && std::isdigit(*it) )
    ++it;

  return !st.empty() && it == st.end();
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
  rtn = Replace( rtn, ">=", "_ge_" );
  rtn = Replace( rtn, "<=", "_le_" );
  rtn = Replace( rtn, "!=", "_ne_" );
  rtn = Replace( rtn, "&&", "_and_" );
  rtn = Replace( rtn, "||", "_or_" );
  rtn = Replace( rtn, "!", "_not_" );
  rtn = Replace( rtn, ">" , "_gt_" );
  rtn = Replace( rtn, "<" , "_lt_" );

  // Arithmetic operators
  rtn = Replace( rtn, "+", "_plus_" );
  rtn = Replace( rtn, "*", "_mul_" );
  rtn = Replace( rtn, "/", "_dev_" );
  rtn = Replace( rtn, "=", "_eq_" );

  // Other operators
  rtn = Replace( rtn, "(" , "_" );
  rtn = Replace( rtn, ")" , "_" );
  rtn = Replace( rtn, "[" , "_" );
  rtn = Replace( rtn, "]" , "_" );

  // __ -> _
  rtn = Replace( rtn, "_" , "__" );

  // Correction for result directory
  rtn = Replace( rtn, "result_dev_", "result/" );

  return rtn;

}


string Subtraction( string s1, string s2 )
{

  if( !(IsNumber(s1) && IsNumber(s2) ) )
    {
      cerr << "string Subtraction( string s1, string s2 )" << endl;
      cerr << s1 << " and/or " << s2 << " are not number" << endl;
      exit(-1);
    }

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

//conversion
int String2Int( string st )
{

  if( IsNumber( st ) == false )
    {

      cerr << "int String2Int( string st )" << endl;
      cerr << st << " contains non number" << endl;
      cerr << "Program is stopped" << endl;
    }

  istringstream iss(st);
  int num;
  iss >> num;

  return num;
}

double String2Double( string st )
{
  stringstream ss(st);
  double val;
  ss >> val;

  return val;
}
