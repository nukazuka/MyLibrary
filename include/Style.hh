#ifndef MYLIB_STYLE_HH
#define MYLIB_STYLE_HH

#include "HeadersRoot.hh"
#include "TStyle.h"
void Style();
void SetHistStyle( TH1D* hist, int color, int width );

// #ifndef __CINT__
template < class TH >
void SetHistStyle( TH* hist, int color, int width )
{

  HistSetting( hist , color , width );
}

template < typename TH > 
void HistSetting( TH* hist , int color = 1 , int line_width = 2 , int fill_style = 0 )
{

  if( hist->fN != hist->GetNcells() )
    if( hist->GetDefaultSumw2() == true )
      hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  hist->SetLineWidth( line_width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
}

//#endif // ifdef __CINT__

//#ifdef __CINT__
//#endif // ifndef __CINT__

//void SetGraphStyle( TGraph* g, int color , int width );
void GraphSetting( TGraph* g, int color = 1, int width = 2 , int marker_style = 20  , int fill_style = 0 );
void SetColorPalette_old( int num = 55 );

#endif // ifndef MYLIB_STYLE_HH