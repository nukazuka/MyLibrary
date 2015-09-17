#ifndef MYLIB_STYLE_HH
#define MYLIB_STYLE_HH

#include "TStyle.h"
void Style();
void SetHistStyle( TH1D* hist, int color, int width );

template < class TH >
void SetHistStyle( TH* hist, int color, int width )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetLineWidth( width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
}

#endif
