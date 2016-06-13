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

  double width, height;

  if ( shape == "square" )
    {
      width  = 1000;
      height = 1000;
    }
  else if ( shape == "landscape" )
    {
      width  = 1200;
      height =  800;
    }
  else if ( shape == "3:2" )
    {
      width  = 1200;
      height =  800;
    }
  else if ( shape == "presen" )
    {
      width  =  255;
      height =  170;
    }
  else if ( shape == "double" )
    {
      width  = 1600;
      height =  800;
    }
  else if ( shape == "triple" )
    {
      width  = 2400;
      height =  800;
    }
  else if ( shape == "quad" )
    {
      width  = 3200;
      height =  800;
    }
  else if ( shape == "comparison" )
    {
      width  = 1000;
      height = 1450;
    }
  else
    {
      width  = 1600;
      height =  900;
    }


  c = new TCanvas( name.c_str(), title.c_str(), width, height );  // 16:9 = 1.78 : 1

  c->SetWindowSize(width + (width - c->GetWw()), height + (height - c->GetWh()));
  gSystem->ProcessEvents();

  if( shape == "comparison" )
    {

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
    }

  c->SetLogy( logy );

  CanvasSetting(c);
  return c;
}
