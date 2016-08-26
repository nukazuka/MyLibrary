#ifndef MYLIB_HISTOPERATION_HH
#define MYLIB_HISTOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "Style.hh"

using namespace std;


/*!
  @fn TObject* GetObject( string file_name, string obj_name)
  @param
  @return
  @brief get root object
 */
//TObject* GetObject( string file_name, string obj_name);

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
  @fn void DrawTitle(TVirtualPad* pad)
  @param
  @return
  @brief
 */
//void DrawTitle(TVirtualPad* pad);


/*
TH1D* GetHist( string name, string title, 
	       int bin, double xmin, double xmax,
	       TTree* tr, string target , string cut );

*/

/*!
template < typename TH >
TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
*/

template < typename TH >
TH* GetHist( string name, string title, 
	     int bin, double xmin, double xmax,
	     TTree* tr, string target , string cut )
{
  
  TH* hist_rtn = new TH( name.c_str(), title.c_str(), bin, xmin, xmax );
  hist_rtn->Sumw2();
  cout << "GetHist::" 
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


template < typename TH > 
void HistSetting( TH* hist , int color , int line_width = 2)
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( line_width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();

}

template < typename TH > 
void HistSetting( TH* hist , int color )
{
  HistSetting( hist , color , 2 );
}

template < typename TH > 
void NormalizeHist( TH* hist )
{
  hist->Scale( 1.0 / hist->Integral() );
}

#endif
