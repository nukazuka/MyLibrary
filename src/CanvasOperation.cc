#ifndef __CINT__
#include "CanvasOperation.hh"
#endif

using namespace std;

void PadSetting() 
{

  gROOT->SetStyle("Modern") ;
  gPad->SetGridx( true );
  gPad->SetGridy( true );
  gPad->SetTicks( true, true );
  gStyle->SetPalette(55, 0, 1 );
  gStyle->SetGridColor( kGray );
  gStyle->SetGridStyle( 3 );
}


void CanvasSetting( )
{

  //  gPad->SetLeftMargin( 0.07 );
  //  gPad->SetLeftMargin( 0.05 );
  //  gPad->SetRightMargin( 0.15 );

  PadSetting();
}

void CanvasSetting( TCanvas* c )
{
  // ? ? ?
  CanvasSetting();
}

TCanvas* GetCanvas( string name, string shape, bool logy=false )
{  
  TCanvas* c;
  string title = "title";

  if ( shape == "square" )
    c = new TCanvas( name.c_str(), title.c_str(), 1000, 1000 );
  else if ( shape == "landscape" )
    c = new TCanvas( name.c_str(), title.c_str(), 1200, 800 );
  else if ( shape == "3:2" )
    c = new TCanvas( name.c_str(), title.c_str(), 1200, 800 );
  else if ( shape == "presen" )
    c = new TCanvas( name.c_str(), title.c_str(), 255, 170 );
  else if ( shape == "double" )
    c = new TCanvas( name.c_str(), title.c_str(), 1600, 800 );
  else
    c = new TCanvas( name.c_str(), title.c_str(), 1600, 900 );

  c->SetLogy( logy );

  CanvasSetting(c);
  return c;
}
