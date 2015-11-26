#ifndef __CINT__
#include "Style.hh"
#endif // __CINT__

void Style()
{

  gStyle->SetEndErrorSize(0);
  gStyle->SetOptFit();
  gStyle->SetFillStyle(0);

}

#ifndef __CINT__
void SetHistStyle( TH1D* hist, int color, int width )
{
  SetHistStyle<TH1D>(hist, color, width);
}
#endif

#ifdef __CINT__

void SetHistStyle( TH1D* hist, int color, int width )
{

  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetLineWidth( width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
}

#endif

void SetGraphStyle( TGraph* g, int color , int width )
{
  g->SetLineColor   ( color );
  g->SetMarkerColor ( color );
  g->SetFillColor   ( color );
  g->SetLineWidth   ( width );
}
