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
  @fn TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
  @brief get a hit with given bin configuration from given tree using given expression and cut
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
  
  TH* hist_rtn = new TH( name.c_str(), title.c_str(), bin, xmin, xmax );
  hist_rtn->Sumw2();
  tr->Draw( (target+">>"+name).c_str() , cut.c_str(), "goff" );
  HistSetting( hist_rtn );
  return hist_rtn;
}

/*!
  @fn TH* GetHist2D( string name, string title, 
  int bin, double xmin, double xmax,
  TTree* tr, string target , string cut )
  @param name name of returned hist
  @param title title of returned hist
  @param xbin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param ybin a number of bin of returned hist
  @param ymin min. range of returned hist
  @param ymax max. range of returned hist
  @param xtarget target to be drawn in xaxis
  @param ytarget target to be drawn in yaxis
  @param cut a cut to be applied
*/
template < typename TH >
TH* GetHist2D( string name, string title, 
	       int xbin, double xmin, double xmax,
	       int ybin, double ymin, double ymax,
	       TTree* tr, string xtarget , string ytarget, string cut )
{
  
  string expression = ytarget + ":" + xtarget;
  return GetHist2D<TH>( name, title,
			xbin, xmin, xmax,
			ybin, ymin, ymax,
			tr, expression, cut );
}

/*!
  @fn TH* GetHist2D( string name, string title, 
  int bin, double xmin, double xmax,
  TTree* tr, string target , string cut )
  @param name name of returned hist
  @param title title of returned hist
  @param xbin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param ybin a number of bin of returned hist
  @param ymin min. range of returned hist
  @param ymax max. range of returned hist
  @param expression used to get hist from TTree::Draw
  @param cut a cut to be applied
*/
template < typename TH >
TH* GetHist2D( string name, string title, 
	       int xbin, double xmin, double xmax,
	       int ybin, double ymin, double ymax,
	       TTree* tr, string expression_arg, string cut )
{
  
  TH* hist_rtn = new TH( name.c_str(), title.c_str(),
			 xbin, xmin, xmax,
			 ybin, ymin, ymax
			 );

  hist_rtn->Sumw2();
  string expression = expression_arg + ">>" + name;

  // for debugging
  // cout << name << endl;
  // cout << title << endl;
  // cout << xbin << " " << xmin << " " << xmax << endl;
  // cout << ybin << " " << ymin << " " << ymax << endl;
  // cout << expression << endl;
  // cout << cut << endl;
      
  tr->Draw( expression.c_str() , cut.c_str(), "goff" );
  HistSetting( hist_rtn );
  return hist_rtn;
}

/*!
  @fn TH* GetHist3D( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
  @param name name of returned hist
  @param title title of returned hist
  @param xbin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param ybin a number of bin of returned hist
  @param ymin min. range of returned hist
  @param ymax max. range of returned hist
  @param zbin a number of bin of returned hist
  @param zmin min. range of returned hist
  @param zmax max. range of returned hist
  @param xtarget target to be drawn in xaxis
  @param ytarget target to be drawn in yaxis
  @param ztarget target to be drawn in zaxis
  @param cut a cut to be applied
*/
template < typename TH >
TH* GetHist3D( string name, string title, 
	       int xbin, double xmin, double xmax,
	       int ybin, double ymin, double ymax,
	       int zbin, double zmin, double zmax,
	       TTree* tr,
	       string xtarget , string ytarget, string ztarget,
	       string cut )
{
  
  string expression = ztarget + ":" + ytarget + ":" + xtarget + ">>" + name;
  return GetHist3D<TH>( name, title,
			xbin, xmin, xmax,
			ybin, ymin, ymax,
			zbin, zmin, zmax,
			tr, expression, cut );
}

/*!
  @fn TH* GetHist3D( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
  @param name name of returned hist
  @param title title of returned hist
  @param xbin a number of bin of returned hist
  @param xmin min. range of returned hist
  @param xmax max. range of returned hist
  @param ybin a number of bin of returned hist
  @param ymin min. range of returned hist
  @param ymax max. range of returned hist
  @param zbin a number of bin of returned hist
  @param zmin min. range of returned hist
  @param zmax max. range of returned hist
  @param xtarget target to be drawn in xaxis
  @param ytarget target to be drawn in yaxis
  @param ztarget target to be drawn in zaxis
  @param cut a cut to be applied
*/
template < typename TH >
TH* GetHist3D( string name, string title, 
	       int xbin, double xmin, double xmax,
	       int ybin, double ymin, double ymax,
	       int zbin, double zmin, double zmax,
	       TTree* tr, string expression_arg, string cut )
{
  
  TH* hist_rtn = new TH( name.c_str(), title.c_str(),
			 xbin, xmin, xmax,
			 ybin, ymin, ymax,
			 zbin, zmin, zmax
			 );
  
  hist_rtn->Sumw2();
  string expression = expression_arg + ">>" + name;
  tr->Draw( expression.c_str() , cut.c_str(), "goff" );
  HistSetting( hist_rtn );

  return hist_rtn;
}


/*!
  @fn vector < TH* > GetHists( string name, string title,
  int bin_num , double xmin, double xmax,
  TTree* tr,
  string expression , string cut_baes ,
  string cut_for_range,  vector < double > vrange 
  )
  @param name base name of histograms. The name of hist without cut has this name. The name of hists with range cut have "name + i".
  @param title title of hists
  @param bin_num a number of bin
  @param xmin minimum range in x axis
  @param xmax maximum range in x axis
  @param tr TTree
  @param expression name of branch which you want to draw
  @param cut_base cuts which are applied to all hists
  @param cut_range a cut to get hists in each region
  @param vrange range for range cut
  @brief a hist and hists applied range cuts are returned
  @details 

*/

template < typename TH >
vector < TH* > GetHists( string name, string title,
			 int bin_num , double xmin, double xmax,
			 TTree* tr,
			 string expression , string cut_base ,
			 string cut_for_range , vector < double > vrange 
			 )
{


  TH* hist = GetHist<TH1D>( name , title, bin_num, xmin, xmax, tr, expression, cut_base );
  HistSetting( hist );

  vector < TH* > vhist;
  vhist.push_back( hist );
  
  for( int i=0; i<vrange.size(); i++ )
    {
      stringstream ss_cut;
      if( i == 0 ) // the first loop
	{
	  ss_cut << cut_for_range << "<" << vrange[i];
	}
      //      else if( i == vrange.size()-1 ) // the last loop
      else if( i == vrange.size() ) // the last loop
	{
	  ss_cut << vrange[i-1] << "<" << cut_for_range ;
	}
      else // normal loop
	{
	  ss_cut << vrange[i-1] << "<" << cut_for_range << " && "
		 << cut_for_range << "<" << vrange[i];
	}

      string this_name = ss_cut.str();
      
      if( cut_base != "" )
	ss_cut << " && " << cut_base;

      TH* hist_temp = GetHist<TH>( this_name , title,
				   bin_num , xmin , xmax ,
				   tr , expression , ss_cut.str() );

      HistSetting( hist_temp , GetColor(i+1) );
      vhist.push_back( hist_temp );

      cout << ss_cut.str() << endl;
    }
  
  return vhist;
}


template < typename TH >
vector < TH* > GetHists( string name, string title,
			 int bin_num , double xmin, double xmax,
			 TTree* tr,
			 string expression , string cut_base ,
			 string cut_for_range ,
			 int div_num , double range_min , double range_max
			 )
{

  double step;
  if( div_num != 0 )
    step = ( range_max - range_min ) / div_num;
  else
    step = ( range_max - range_min );

  vector < double > vrange;
  for( int i=0; i<div_num; i++ )
    vrange.push_back( range_min + i * step );

  
  return GetHists< TH* >( name          , title    ,
			  bin_num       , xmin     , xmax ,
			  tr            ,
			  expression    , cut_base ,
			  cut_for_range , vrange   );
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
int GetOverflowNum( TH* hist )
{
  return hist->GetBinContent( hist->GetXbinsX() + 1 );
}

template < typename TH >
int GetUnderflowNum( TH* hist )
{
  return hist->GetBinContent( 0 );
}

template < typename TH >
int GetOverflowAndUnderflowNum( TH* hist )
{
  return GetOverflowNum( hist ) + GetUnderflowNum( hist );
}


template < typename TH >
int GetOverflowNum2DX( TH* hist )
{
  int rtn = 0;
  for( int i=0; i<hist->GetNibnsY(); i++ )
    rtn += hist->GetBinContent( hist->GetNbinsX()+1 , i );

  return rtn;
}

/*!
  @fn int GetOverflowUnderflowNum2D( TH* hist , bool bl_x_over , bool bl_y_over , bool bl_and )
  @param hist 2D histogram
  @param bl_x_over a flag for x axis. true means overflow and false means underflow
  @param bl_y_over a flag for y axis. true means overflow and false means underflow
  @param conbination 0 means AND. AND of x and y is returned. 
  1 means OR. OR of x and y is returned. 
  2 means ONLY X. Sum of overflow or underflow in x axis is returned.
  3 means ONLY Y. Sum of overflow or underflow in y axis is returned.
  4 means ALL. All entries in overflow and underflow bins are returned.
 */
template < typename TH >
int GetOverflowUnderflowNum2D( TH* hist , bool bl_x_over , bool bl_y_over , int conbination = 1 )
{

  int bin_x = 0;
  if( bl_x_over )
    bin_x = hist->GetNbinsX() + 1;

  int bin_y = 0;
  if( bl_y_over )
    bin_y = hist->GetNbinsY() + 1;
  
  if( conbination == 0 ) // AND
    return hist->GetBinContent( bin_x , bin_y );

  // |uo|oooooooooooooo|oo|  - o : overflow
  // |u |              |o |  - u : underflow
  // |u |    hist      |o |
  // |u |              |o |
  // |uu|uuuuuuuuuuuuuu|ou|
  //
  // conbination 0 returns uu, uo, ou, or oo 
  // conbination 1 returns sum(x-flag) + sum(y-flag) + 
  
  if( conbination == 4 ) // ALL
    return GetOverflowUnderflowNum2D < TH > ( hist , true  , true  , 1 ) // x-over  || y-over
      + GetOverflowUnderflowNum2D    < TH > ( hist , false , false , 1 ) // y-under || y-under
      - GetOverflowUnderflowNum2D    < TH > ( hist , true  , false , 0 ) // x-over  && y-under
      - GetOverflowUnderflowNum2D    < TH > ( hist , false , true  , 0 );// x-under && y-over

  int sum_x = 0;
  // loop over overflow (underflow) bins of x
  for( int i=0; i<hist->GetNbinsY(); i++ )
      sum_x += hist->GetBinContent( bin_x , i );

  if( conbination == 2 ) // only x
    return sum_x;
  
  int sum_y = 0;
  // loop over overflow (underflow) bins of y
  for( int i=0; i<hist->GetNbinsX(); i++ )
    sum_y += hist->GetBinContent( i, bin_y );

  if( conbination == 3 ) // only y
    return sum_y;

  // conbination == 1, OR
  return sum_x + sum_y - GetOverflowUnderflowNum2D<TH>( hist , bl_x_over , bl_y_over, 0 ); // subtract overlapping bin ( x && y )
}



template < typename TH >
vector < TH* > GetVectorHist( vector < string >& vname, vector < string >& vtitle, 
			      int bin, double xmin, double xmax,
			      vector < TTree* > &vtr, string target , vector < string >& vcut )
{

  vector < TH* > vhist;
  for( int i=0; i<vtr.size(); i++ )
    {
      vhist.push_back( GetHist<TH>( vname[i], vtitle[i], bin, xmin, xmax, vtr[i], target , vcut[i] ) );
      HistSetting( vhist[i], GetColor(i), 2 );
    }
  
  return vhist;
}

template < typename TH >
vector < TH* > GetVectorHist( string name, string title, 
			      int bin, double xmin, double xmax,
			      vector < TTree* > &vtr, string target , string cut )
{


  vector < string > vname, vtitle, vcut;
  vector < TH* > vhist;
  for( int i=0; i<vtr.size(); i++ )
    {
      vname.push_back( (string)"name" + Int2String(i+1) );
      vtitle.push_back( (string)"title" + Int2String(i+1) );
      vcut.push_back( cut );
      //      vhist.push_back( GetHist<TH>( name, title, bin, xmin, xmax, vtr[i], target , cut ) );
      //      HistSetting( vhist[i], GetColor(i), 2 );
    }
  
  //  return vhist;
  return GetVectorHist<TH>( vname, vtitle, bin, xmin, xmax, vtr, target, vcut );
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
void HistSetting( TH* hist ,
		  int color = 1,
		  int line_width = 2,
		  int marker_style = 20,
		  int line_style = 1 )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( line_width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetZaxis()->CenterTitle();
  hist->SetMarkerStyle( marker_style );
  hist->SetLineStyle( line_style );
  
}

template < typename TH > 
void NormalizeHist( TH* hist , double val = 1.0 )
{
  if( hist->Integral() != 0 )
    hist->Scale( val / hist->Integral() );
  else
    cerr << "void NormalizeHist, " << hist->GetName() << " cannot be normalized since it has no entry" << endl;
  
}

#ifdef __CINT__
#include "../src/HistOperation.cc"
#endif

#endif
