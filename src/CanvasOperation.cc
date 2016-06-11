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
  gStyle->SetEndErrorSize(0) ;
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
    c = new TCanvas( name.c_str(), title.c_str(), 1000, 1000 ); // 1:1
  else if ( shape == "landscape" )
    c = new TCanvas( name.c_str(), title.c_str(), 1200, 800 );  // 3:2 = 1.5 : 1
  else if ( shape == "3:2" )
    c = new TCanvas( name.c_str(), title.c_str(), 1200, 800 );  // 3:2 = 1.5 : 1
  else if ( shape == "presen" )
    c = new TCanvas( name.c_str(), title.c_str(), 255, 170 );   // 1.5 : 1
  else if ( shape == "double" )
    c = new TCanvas( name.c_str(), title.c_str(), 1600, 800 );  // 2:1
  else if ( shape == "triple" )
    c = new TCanvas( name.c_str(), title.c_str(), 2400, 800 );  // 3:1
  else if ( shape == "quad" )
    c = new TCanvas( name.c_str(), title.c_str(), 3200, 800 );  // 4:1
  else if ( shape == "comparison" )
    {

      c = new TCanvas( name.c_str(), title.c_str(), 1000, 1450 );  // 1000*1000 and 250*1000

      //    -------------------------
      //    |//////// title /////// |  100   
      //    |                       |       
      //    |                       |       
      //    |           #1          | 
      //    |         Hists         | 1000
      //    |                       |
      //    |                       |
      //    |-----------------------|
      //    |           #2          |
      //    |         Ratio         |  250
      //    |                       |  
      //    |///// axis title //////|  100
      //    -------------------------
      //    <--------- 1000 -------->

      double ratio = 1.0 - 1100.0 / 1450.0;
      TPad *pad1 = new TPad("pad1", "title", 0.0, ratio , 1.0, 1.0 , -1, -1, -2 );
      pad1->SetTopMargin( 100.0 / 1100.0 );
      pad1->SetBottomMargin( 0.001 );
      pad1->Draw();
      pad1->SetNumber(1);

      TPad *pad2 = new TPad("pad2", "title", 0.0, 0.0, 1.0, ratio , -1, -1, -2 );
      pad2->SetTopMargin( 0.001 );
      pad2->SetBottomMargin( 100.0 / 350.0 );
      pad2->Draw();
      pad2->SetNumber(2);

      c->cd( 1 );
      PadSetting();

      c->cd( 2 );
      PadSetting();

  /*
    TPad *pad = new TPad("name", "title",xlow,ylow,xup,yup,color, bordersize,bordermode);
    pad->Draw();
    pad->SetNumber(n);
  */


    }
  else
    c = new TCanvas( name.c_str(), title.c_str(), 1600, 900 );  // 16:9 = 1.78 : 1

  c->SetLogy( logy );

  CanvasSetting(c);
  return c;
}
