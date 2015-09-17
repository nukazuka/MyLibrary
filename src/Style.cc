#ifndef __CINT__
#include "Style.hh"
#endif // __CINT__

void Style()
{

  gStyle->SetEndErrorSize(0);
  gStyle->SetOptFit();
  gStyle->SetFillStyle(0);

}


void SetHistStyle( TH1D* hist, int color, int width )
{
  /*
  hist->Sumw2();
  hist->SetLineColor( color );
  hist->SetLineWidth( width );
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  */

  SetHistStyle<TH1D>(hist, color, width);
}
