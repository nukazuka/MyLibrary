#ifndef __CINT__
#include "HistOperation.hh"
#endif

// this must be temp.
#include "HistOperation.hh"
using namespace std;

/*
TH1D* GetHist( string name, string title, 
	       int bin, double xmin, double xmax,
	       TTree* tr, string target , string cut )
{

  TH1D* hist_rtn = new TH1D( name.c_str(), title.c_str(), bin, xmin, xmax );
  HistSetting( hist_rtn , kBlack, 2 );
  hist_rtn->Sumw2();
  tr->Draw( (target+">>"+name).c_str() , cut.c_str(), "goff" );

  return hist_rtn;
}
*/

/*
void HistSetting( TH1* hist )
{

  hist->Sumw2();
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
}


void HistSetting( TH1* hist , int color)
{

  hist->SetLineWidth( 2 );
  hist->SetLineColor( color );
  hist->SetMarkerColor( color );
  HistSetting( hist );
}
*/
