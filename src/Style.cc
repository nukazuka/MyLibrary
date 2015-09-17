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
