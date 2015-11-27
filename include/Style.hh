#ifndef MYLIB_STYLE_HH
#define MYLIB_STYLE_HH

#include "HeadersRoot.hh"
#include "TStyle.h"
void Style();
void SetHistStyle( TH1D* hist, int color, int width );

#ifndef __CINT__
template < class TH >
void SetHistStyle( TH* hist, int color, int width )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetLineWidth( width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
}
#endif // ifdef __CINT__

#ifdef __CINT__
#endif // ifndef __CINT__

#endif // ifndef MYLIB_STYLE_HH

void SetGraphStyle( TGraph* g, int color , int width );
