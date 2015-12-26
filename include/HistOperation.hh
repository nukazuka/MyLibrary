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

/*
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

template < typename TH > 
void HistSetting( TH* hist , int color )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( 2 );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();

}


#endif
