#ifndef MYLIB_TFOREST_HH
#define MYLIB_TFOREST_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

#include "HistOperation.hh"
#include "StringOperation.hh"

using namespace std;
class TForest
{
private:
  string name_;
  string title_;
  
  vector < TTree* > vtr_;
  vector < double > vfactor_;

  void Init();
  int CheckExpressionDimension( string expression );
  
public:
  TForest(){};
  TForest( string name , string title );
  //  TForest TForest( string file , string tree_name );

  void AddTree( TTree* tr , double factor );
  void AddTree( string file, string tree_name , double factor );

  void Draw( string expression , string cut , string option );
  //  Long64_t Draw (const char *varexp, const TCut &selection, Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0)
  double GetFactor( int num );
  vector < double > GetFactors(){ return vfactor_; };

  template < typename TH >
  TH* GetHist( string expression = "" , string cut = "" , int num = 0 ,
	       int bin_x = 1 , double xmin = 0, double xmax = 0 ,
	       int bin_y = 1 , double ymin = 0, double ymax = 0 ,
	       int bin_z = 1 , double zmin = 0, double zmax = 0
	       )
  {
    assert( 0 <= num && num < vtr_.size() );

    TH* rtn = new TH();
    string hist_name = name_ + Int2String( num );
    if( expression == 1 )
      rtn = GetHist<TH>( hist_name , "title",
			 bin_x, xmin, xmax,
			 expression, cut );
    else if( expression == 2 )
      rtn = GetHist2D<TH>( hist_name , "title",
			   bin_x, xmin, xmax,
			   bin_y, ymin, ymax,
			   expression, cut );
    //    else if( expression == 3 )
    
    HistSetting( rtn );
    return rtn;
  }

  
  template < typename TH >
  vector < TH* > GetHists( string expression, string cut, int num,
			   int bin_x = 1 , double xmin = 0, double xmax = 0 ,
			   int bin_y = 1 , double ymin = 0, double ymax = 0 ,
			   int bin_z = 1 , double zmin = 0, double zmax = 0
			   )
  {
    vector < TH* > vrtn;
    for( int i=0; i<vtr_.size(); i++ )
      vrtn.push_back( GetHist<TH>( expression, cut, num,
				   bin_x, xmin, xmax, 
				   bin_y, ymin, ymax, 
				   bin_z, zmin, zmax
				   ) );

    return vrtn;
  }
  
  string GetName(){ return name_; };
  string GetTitle(){ return title_; };
  TTree* GetTree( int num );
  vector < TTree* > GetTrees(){ return vtr_; };

  void SetName( string arg ){ name_ = arg; };
  void SetTitle( string arg ){ title_ = arg;};
};
  
#endif
