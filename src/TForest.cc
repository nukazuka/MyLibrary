#include "TForest.hh"

using namespace std;



//////////////////////////////////////////////////
// constructors                                 //
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// init                                         //
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// private functions                            //
//////////////////////////////////////////////////

int CheckExpressionDimension( string expression )
{
  int dimension = CountCharactor( expression , ":" );

  if( dimension == 0 )
    return 1;
  else if( dimension == 1 )
    return 2;
  else if( dimension == 2 )
    return 3;
  else
    {
      cerr << "int CheckExpressionDimension( string expression )" << endl
	   << "dimension(# of :) is " << dimension << endl
	   << "It's strange!!!";
    }

  return -1; //dummy  
}

//////////////////////////////////////////////////
// public functions                             //
//////////////////////////////////////////////////
void TForest::AddTree( TTree* tr , double factor )
{
  vtr_.push_back( tr );
  vfactor_.push_back( factor );
}

void TForest::AddTree( string file, string tree_name , double factor )
{
  TFile* tf = new TFile( file.c_str() , "READ" );
  if( tf->IsZombie() )
    {
      cerr << "void TForest::AddTree( string file, string tree_name , double factor )" << endl
	   << file << " is not found" << endl;
      return;
    }

  TTree* tr = (TTree*)tf->Get( tree_name.c_str() );
  return AddTree( tr, factor );
}

void TForest::Draw( string expression , string cut , string option )
{
  //  if( vtr_.size() == 0 || vfactor_.size() == 0 )
  //    cerr << "

  if( vtr_.size() != vfactor_.size() )
    {
      cerr << "void TForetst::Draw( string expression , string cut , string option )"
	   << "size of TTrees and factors are not same!!!" << endl;
      return;
    }




}

double TForest::GetFactor( int num )
{
  assert( num < vfactor_.size() );
  return vfactor_[num];
}

TTree* TForest::GetTree( int num )
{
  assert( num < vtr_.size() );
  return vtr_[num];
}
