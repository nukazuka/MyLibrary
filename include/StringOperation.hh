#ifndef MYLIB_STRINGOPERATION_HH
#define MYLIB_STRINGOPERATION_HH

#include <string>
#include <istream>
#include <sstream>

using namespace std;
string GetBaseName( string path );
string GetFileName( string path );
string GetPathToFile( string path);
string GetRepeatedWords( string word, int num );
string GetSuffix( string path );
string Replace( string word, string old_key, string new_key );
string Replace4Cut( string cut );

string Subtraction( string s1, string s2 );
int String2Int( string st );
string Int2String( int num );
double String2Double( string st );
string Double2String( double num );

#endif
