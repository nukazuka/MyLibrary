#ifndef MYLIB_STRINGOPERATION_HH
#define MYLIB_STRINGOPERATION_HH

#include <string>
#include <istream>
#include <sstream>

using namespace std;
/*!
  @fn string GetBaseName( string path )
  @param 
  @return
  @brief
 */
string GetBaseName( string path );

/*!
  @fn string GetFileName( string path )
  @param string path : ファイルのフルパス
  @return 拡張子を含んだファイル名
  @brief ファイルのフルパスから拡張子を含んだファイル名を返す。
 */
string GetFileName( string path );

/*!
  @fn string GetPathToFile( string path)
  @param string path : ファイルのフルパス
  @return ファイルのあるディレクトリまでのパス
  @brief ファイルのフルパスからファイルのあるディレクトリまでのパスを返す。
 */
string GetPathToFile( string path );

/*!
  @fn string GetRepeatedWords( string word, int num )
  @param
  @return
  @brief
 */
string GetRepeatedWords( string word, int num );

/*!
  @fn string GetSuffix( string path )
  @param
  @return
  @brief
 */
string GetSuffix( string path );

/*!
  @fn string Replace( string word, string old_key, string new_key )
  @param
  @return
  @brief
 */
string Replace( string word, string old_key, string new_key );

/*!
  @fn string Replace4Cut( string cut )
  @param
  @return
  @brief
 */
string Replace4Cut( string cut );

/*!
  @fn string Subtraction( string s1, string s2 )
  @param
  @return
  @brief
 */
string Subtraction( string s1, string s2 );

/*!
  @fn int String2Int( string st )
  @param
  @return
  @brief
 */
int String2Int( string st );

/*!
  @fn string Int2String( int num )
  @param
  @return
  @brief
 */
string Int2String( int num );

/*!
  @fn double String2Double( string st )
  @param
  @return
  @brief
 */
double String2Double( string st );

/*!
  @fn string Double2String( double num )
  @param
  @return
  @brief
 */
string Double2String( double num );

/*!
  @fn bool IsNumber( string st )
  @param
  @return
  @brief
 */
bool IsNumber( string st );
#endif
