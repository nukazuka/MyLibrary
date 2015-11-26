#ifndef MYLIB_HISTOPERATION_HH
#define MYLIB_HISTOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

/*!
  @fn void DrawTitle(TVirtualPad* pad)
  @param
  @return
  @brief
 */
//void DrawTitle(TVirtualPad* pad);

template < type TH > 
void HistSetting( TH* hist , int color )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( 2 );
}


#endif
