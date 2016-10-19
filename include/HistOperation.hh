#ifndef MYLIB_HISTOPERATION_HH
#define MYLIB_HISTOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "StringOperation.hh"
#include "Style.hh"

using namespace std;

static int id_for_hist_operation = 0;

/*!
  @fn void HistSetting( TH1* hist )
  @param hist A pointer of histogram
  @details
*/

//void HistSetting( TH1* hist );

/*!
  @fn void HistSetting( TH1* hist, int color )
  @param hist A pointer of histogram
  @param color 
  @details
*/
//void HistSetting( TH1* hist, int color );


/*!
template < typename TH >
TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
*/

/*!
  @fn TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
  @param name name of returned hist
  @param title title of returned hist
  @param bin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param cut a cut to be applied
*/
template < typename TH >
TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
{
  
  cout << "GetHist::" 
       << setw(15) << target << " >> " 
       << setw(15) << name   << "\t" 
       << cut ;
  TH* hist_rtn = new TH( name.c_str(), title.c_str(), bin, xmin, xmax );
  hist_rtn->Sumw2();
  tr->Draw( (target+">>"+name).c_str() , cut.c_str(), "goff" );

  cout << " : done" << endl;
  return hist_rtn;
}

/*!

  @fn TH* GetHistWithWithoutCut( string name, string title, 
  int bin, double xmin, double xmax,
  TTree* tr, string target , string cut, string cut_check )
  @brief cut_check の有無の割合ヒストグラムを返す
  @param name name of returned hist
  @param title title of returned hist
  @param bin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param cut a cut to be applied
  @param cht_check retured hist is the ratio of (entry with this cut) / (entry without this cut)
  @details
*/

template < typename TH >
TH* GetHistWithWithoutCut( string name, string title, 
			   int bin, double xmin, double xmax,
			   TTree* tr, string target , string cut, string cut_check )
{

  if( cut_check == "" )
    {
      cerr << "TH* GetHistWithWithoutCut( string name, string title," << endl;
      cerr << "\tint bin, double xmin, double xmax," << endl;
      cerr << "\tTTree* tr, string target , string cut, string cut_check )" << endl;
      cerr << "cut_check must no be \"\"" << endl;
      exit(-1);
    }

  ///////////////////////////////////////////////////
  // hist without cut_check /////////////////////////  
  string hist_name_without = (string)"HistOperation_GetHistWithWithoutCut"
    + Int2String( id_for_hist_operation );
  id_for_hist_operation++;

  TH* hist_without = GetHist<TH>( hist_name_without, "title_without" ,
				  bin, xmin, xmax,
				  tr, target , cut
				  );

  ///////////////////////////////////////////////////
  // hist with cut_check ////////////////////////////
  string hist_name_with = (string)"HistOperation_GetHistWithWithoutCut"
    + Int2String( id_for_hist_operation);
  id_for_hist_operation++;  

  cut += " && " + cut_check;
  TH* hist_with = GetHist<TH>( hist_name_with , "title" ,
			       bin, xmin, xmax,
			       tr , target , cut
			       );
  
  cout << "GetHistWithWithoutCut::" 
       << setw(15) << target << " >> " 
       << setw(15) << name   << "\t" 
       << cut << "\t with or without "
       << cut_check;

  TH* hist_rtn = (TH*)hist_with->Clone();
  hist_rtn->SetName( name.c_str() );
  hist_rtn->SetTitle( title.c_str() );
  HistSetting( hist_rtn );
  hist_rtn->Divide( hist_without );
  
  cout << " : done" << endl;
  //  tr->Draw( (target+">>"+name).c_str() , cut.c_str(), "goff" );
  return hist_rtn;
}

template < typename TH >
TH* GetHist2D( string name, string title, 
	       int binx, double xmin, double xmax,
	       int biny, double ymin, double ymax,
	       TTree* tr, string target , string cut )
{
  
  TH* hist_rtn = new TH( name.c_str(), title.c_str(), binx, xmin, xmax, biny, ymin, ymax );
  hist_rtn->Sumw2();
  cout << "GetHist2D::" 
       << setw(15) << target << " >> " 
       << setw(15) << name   << "\t" 
       << cut << endl;
  tr->Draw( (target+">>"+name).c_str() , cut.c_str(), "goff" );
  return hist_rtn;
}

/*
template < typename TH >
double GetMaxVal( TH* hist )
{
  


}
*/

template < typename TH >
TH* GetHistFromGraph( TGraph* g , string hist_name )
{

  int num = g->GetN();
  double *val_y  = g->GetY();
  vector < double > vtemp;
  for( int i=0; i<num; i++ )
    vtemp.push_back( val_y[i] );
  
  TH* hist = new TH( hist_name.c_str(), "title",
		     num , 
		     *min_element( vtemp.begin(), vtemp.end()) , 
		     *min_element( vtemp.begin(), vtemp.end())
		     );

  for( int i=0; i<num; i++ )
    hist->SetBinContent( i+1 , val_y[i] );
  
  return hist;
}


template < typename TH >
vector < TH* > GetVectorHist( string name, string title, 
			      int bin, double xmin, double xmax,
			      vector < TTree* > &vtr, string target , string cut )
{

  vector < TH* > vhist;
  for( int i=0; i<vtr.size(); i++ )
    {
      vhist.push_back( GetHist<TH>( name, title, bin, xmin, xmax, vtr[i], target , cut ) );
      HistSetting( vhist[i], GetColor(i), 2 );
    }
  
  return vhist;
}

template < typename TH >
int GetMaxBinContent( TH* hist )
{
  vector < int > vcontent;
  for( int i=0; i < hist->GetNbinsX(); i++ )
    vcontent.push_back( hist->GetBinContent( i+1 ) );

  return *max_element( vcontent.begin(), vcontent.end() );
}

template < typename TH >
int GetMinBinContent( TH* hist , bool bl_ignote_negative )
{

  vector < int > vcontent;

  for( int i=0; i < hist->GetNbinsX(); i++ )
    // if this content is larget than 0, just take it
    if( hist->GetBinContent( i+1 ) > 0 )
      {
	vcontent.push_back( hist->GetBinContent( i+1 ) );
      }
  // if this content is 0 or negative, check flag
    else 
      {
	// if flag is false, take it
	if( bl_ignote_negative == false )
	  {
	    vcontent.push_back( hist->GetBinContent( i+1 ) );
	  }
      }

    return *min_element( vcontent.begin(), vcontent.end() );
}

template < typename TH >
int GetMinBinContent( TH* hist )
{
  return GetMinBinContent( hist , false );
}

template < typename TH >
int GetBinWithMaxContent( TH* hist )
{

  int max_content = GetMaxBinContent( hist );
  for( int i=0; i < hist->GetNbinsX(); i++ )
    if( hist->GetBinContent( i+1 ) == max_content )
      return i+1;

  return -1;
}

/*!
  @fn int GetBinWith( TH* hist , double bin_center )
  @brief Get index of the bin which contains bin_center
  @tparam hist histogram, should be TH1*
  @param bin_center this is the value that returned bin contains
*/

template < typename TH >
int GetBinAt( TH* hist , double bin_center )
{
  int rtn = -1;
  double diff = 1e5;
  for( int i=0; i<hist->GetNbinsX(); i++ )
    {
      double temp = abs( hist->GetBinCenter( i+1 ) - bin_center );
      if( temp < diff )
	{
	  diff = temp;
	  rtn = i+1;
	}
    }
  return rtn;
}

template < typename TH > 
void HistSetting( TH* hist , int color = 1, int line_width = 2, int marker_style = 20 )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( line_width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetMarkerStyle( marker_style );
  
}

template < typename TH > 
void NormalizeHist( TH* hist , double val = 1.0 )
{
hist->Scale( val / hist->Integral() );
}

#ifdef __CINT__
#include "../src/HistOperation.cc"
#endif

#endif
