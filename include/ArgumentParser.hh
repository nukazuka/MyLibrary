#ifndef ARGUMENTPARSER_HH
#define ARGUMENTPARSER_HH

/*!
  @file ArgumentParser.hh
*/

#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <vector>
#include <algorithm>

/*!
  @class ArgumentParser
  @brief
  @author G.Nukazuka
  @date 2015/02/05
  @details
  @todo add explanations
*/

using namespace std;
class ArgumentParser
{
private : 

  vector < string > vtype_;
  vector < string > varg_;

  int    GetIndex( string type );
  void   long_version( string arg, string& type, string& arg_rt );
  string short_version( string arg );
  void   MergeArgument( string type, string state );
public :

  ArgumentParser( int argc, char* argv[] );

  string GetArgument( string type );
  int    GetArgumentNum(){ return vtype_.size(); };
  bool   IsSpecified( string type );
  void   ShowAll();
};
#endif
