#ifndef MYLIB_HISTOPERATION_HH
#define MYLIB_HISTOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

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
  @detail
*/

//void HistSetting( TH1* hist );

/*!
  @fn void HistSetting( TH1* hist, int color )
  @param hist A pointer of histogram
  @param color 
  @detail
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
