#ifndef MYLIB_STRINGOPERATION_HH
#define MYLIB_STRINGOPERATION_HH

#include <string>
#include <istream>
#include <sstream>
#include <iostram>
#include <cstdlib>

using namespace std;
/*!
  @fn string GetBaseName( string path )
  @param path : ファイルのフルパス
  @return パスと拡張子を除いたファイル名（ex. src/test.cc -> test）
  @brief ファイルのフルパスからパスと拡張子を除いたファイル名を返す。
 */
string GetBaseName( string path );

/*!
  @fn string GetFileName( string path )
  @param path : ファイルのフルパス
  @return 拡張子を含んだファイル名
  @brief ファイルのフルパスから拡張子を含んだファイル名を返す。
 */
string GetFileName( string path );

/*!
  @fn string GetPathToFile( string path)
  @param path : ファイルのフルパス
  @return ファイルのあるディレクトリまでのパス
  @brief ファイルのフルパスからファイルのあるディレクトリまでのパスを返す。
 */
string GetPathToFile( string path );

/*!
  @fn string GetRepeatedWords( string word, int num )
  @param word : 繰り返される文字列
  @param int num : 繰り返す回数
  @return num 個の word 
  @brief word を num 回繰り返した文字列を返す。コメントを表示するときなどに便利。
 */
string GetRepeatedWords( string word, int num );

/*!
  @fn string GetSuffix( string path )
  @param path : ファイル名またはファイルのフルパス。
  @return ファイルの拡張子（ex. .cc ）
  @brief ファイル名やファイルのフルパスからファイルの拡張子を返す。
 */
string GetSuffix( string path );

/*!
  @fn string Replace( string word, string old_key, string new_key )
  @param word : 対象となる文字列。
  @param old_key : 置換される文字列。
  @param new_key : 置換する文字列。
  @return word にある old_key を new_key に置き換えた文字列。
  @brief word から old_key を探し， new_key に置き換えた文字列を返す。word は変更しない。
 */
string Replace( string word, string old_key, string new_key );

/*!
  @details 以下のように変換される。

 前   | 後 |
 ---: | -----:   |
 " "  | \_       |
 ==   | \_eq\_   |
 \>   | \_gt\_   |
 \>=  | \_ge\_   |
 <    | \_lt\_   |
 <=   | \_le\_   |
 !=   | \_ne\_   |
 &&   | \_and\_  |
 \|\| | \_or\_   |
 !    | \_not\_  |
 +    | \_plus\_ |
 \*   | \_mul\_  |
 /    | \_dev\_  |
 (    | \_       |
 )    | \_       |
 [    | \_       |
 ]    | \_       |

  @fn string Replace4Cut( string cut )
  @param cut : 対象となる文字列
  @brief ファイル名に cut 情報をのせるために作った。
  @return cut にある C/C++ の関係演算子を文字列に置き換えたもの。

 */
string Replace4Cut( string cut );

/*!
  @fn string Subtraction( string s1, string s2 )
  @param[in] s1 : 引かれる文字列
  @param[in] s2 : 引く文字列
  @return s1 - s2 の結果を文字列として返す。
  @brief 数字のみでできた文字列間の計算 s1 - s2 を行い，結果を文字列として返す。
  @details 文字列に数字でないものが含まれていたときは，エラーを表示しプログラムを停止させる。
 */
string Subtraction( string s1, string s2 );

/*!
  @fn int String2Int( string st )
  @param[in] st : 変換される文字列
  @return st を int 型にしたもの。
  @brief 数字のみからなる文字列を int 型に変換し返す。
 */
int String2Int( string st );

/*!
  @fn string Int2String( int num )
  @param num : 変換される int 型の数字。
  @return num を文字列に変換したもの。
  @brief int を string 型に変換し返す。
 */
string Int2String( int num );

/*!
  @fn double String2Double( string st )
  @param st : 変換される double 型の数字。
  @return st を double 型に変換したもの。
  @brief 数字のみからなる文字列を double 型に変換し返す。
 */
double String2Double( string st );

/*!
  @fn string Double2String( double num )
  @param num : 変換される double 型の数字。
  @return num を文字列に変換したもの。
  @brief double を strgin 型に変換し，返す。
  @details 有効数字をどうするかまだ決めていない.
  @todo 有効数字をどうするか？ */
string Double2String( double num );

/*!
  @fn bool IsNumber( string st )
  @param st : 判定する文字列。
  @retval true : 文字列が数字のみから構成されている時。
  @retval false : 文字列に数字以外の文字が含まれている時。
  @brief 文字列が数字のみで構成されているかを判定する。
 */
bool IsNumber( string st );
#endif
