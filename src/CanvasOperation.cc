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

// I just took this from official tutrial ( tutrial/graphics/canvas2.C )
void CanvasPartition(TCanvas *C,const Int_t Nx,const Int_t Ny,
                     Float_t lMargin, Float_t rMargin,
                     Float_t bMargin, Float_t tMargin)
{
  if (!C) return;

  // Setup Pad layout:
  Float_t vSpacing = 0.0;
  Float_t vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;

  Float_t hSpacing = 0.0;
  Float_t hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;

  Float_t vposd,vposu,vmard,vmaru,vfactor;
  Float_t hposl,hposr,hmarl,hmarr,hfactor;

  for (Int_t j=0;j<Ny;j++) {

    // top line 
    if ( j==0 ) {
      vposu = 1.;
      vposd = vposu - vStep - tMargin;
      vfactor = vposu-vposd;
      vmard = 0.0;
      vmaru = bMargin / (vposu-vposd);
    }
    else if(j == Ny-1){ // bottom line 
      vposu = vposd - vSpacing;
      vposd = 0.0;
      vfactor = vposu-vposd;
      vmard = tMargin / vfactor;
      vmaru = 0.0;
    }
    else { // other lines
      vposu = vposd - vSpacing;
      vposd = vposu - vStep;
      vfactor = vposu-vposd;
      vmard = 0.0;
      vmaru = 0.0;
    }

    for (Int_t i=0;i<Nx;i++) {
       
      if (i==0) { // left line
	hposl = 0.0;
	hposr = lMargin + hStep;
	hfactor = hposr-hposl;
	hmarl = lMargin / hfactor;
	hmarr = 0.0;
      } else if (i == Nx-1) { // right line
	hposl = hposr + hSpacing;
	hposr = hposl + hStep + rMargin;
	hfactor = hposr-hposl;
	hmarl = 0.0;
	hmarr = rMargin / (hposr-hposl);
      } else {
	hposl = hposr + hSpacing;
	hposr = hposl + hStep;
	hfactor = hposr-hposl;
	hmarl = 0.0;
	hmarr = 0.0;
      }
       
       
      C->cd(0);
	 
      char name[16];
      sprintf(name,"pad_%i_%i",i,j);
      TPad *pad = (TPad*) gROOT->FindObject(name);
      if (pad) delete pad;
      pad = new TPad(name,"",hposl,vposd,hposr,vposu);
      pad->SetLeftMargin(hmarl);
      pad->SetRightMargin(hmarr);
      pad->SetBottomMargin(vmard);
      pad->SetTopMargin(vmaru);

      pad->SetFrameBorderMode(0);
      pad->SetBorderMode(0);
      pad->SetBorderSize(0);

      pad->Draw();

      int num = (i+1) + Ny*(j);
      pad->SetNumber( num );
      /*	 
      cout << "Pad#" << setw(2) << num << " | "
	   << setw(10) << setprecision(5) << hposl << " , " 
	   << setw(10) << setprecision(5) << vposd << " , " 
	   << setw(10) << setprecision(5) << hposr << " , " 
	   << setw(10) << setprecision(5) << vposu 
	   <<  endl;
      */
    }
  }
}

void DivideEqually( TCanvas*c , int nx, int ny, double lMargin, double rMargin, double bMargin, double tMargin, int color)
{

  // Canvas setup
  CanvasPartition( c, nx, ny, lMargin, rMargin, bMargin, tMargin);

  TPad *pad[nx][ny];
  for (Int_t i=0;i<nx;i++)
    {
      for (Int_t j=0;j<ny;j++)
	{
	   
	  c->cd(0);
	   
	  // Get the pads previosly created.
	  char pname[16];
	  sprintf(pname,"pad_%i_%i",i,j);
	  pad[i][j] = (TPad*) gROOT->FindObject(pname);
	  pad[i][j]->Draw();
	  pad[i][j]->SetFillStyle(4000);
	  pad[i][j]->SetFrameFillStyle(4000);
	  pad[i][j]->cd();
	}
    }

  int counter = 1;
  for (Int_t i=nx-1;i<-1;i--)
    {
      for (Int_t j=0;j<ny;j++)
	{
	  pad[i][j]->SetNumber( counter );
	  counter++;
	}
    }
  c->cd();
}

void DivideEqually( TCanvas*c , int nx, int ny, double xmargin = 0.01 , double ymargin = 0.01 , int color = 0 )
{

  DivideEqually( c , nx, ny, xmargin, xmargin, ymargin, ymargin, color );
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

      width  = 1200;
      height = 1500;
    }
  else
    {
      width  = 1600;
      height =  900;
    }


  c = new TCanvas( name.c_str(), title.c_str(), width, height );

  c->SetWindowSize(width + (width - c->GetWw()), height + (height - c->GetWh()));
  gSystem->ProcessEvents();

  if( shape == "comparison" )
    {

      //    -------------------------------------  
      //    |   /////////// title ///////////   |  <- 125   
      //    | m |                           | m |       
      //    |   |                           |   |       
      //    | a |             #1            | a | 
      //    |   |           Hists           |   |  <- 1000
      //    | r |          (square)         | r |
      //    |   |                           |   |
      //    | g |---------------------------| g |
      //    |   |             #2            |   |
      //    | i |            Ratio          | i |  <- 250
      //    |   |                           |   |  
      //    | n |/////// axis title ////////| n |  <-  80
      //    |-----------------------------------|

      //    |<-->|<----------------------->|<-->|
      //    | 100|           1000          | 100|
      //    |<-------------- 1200 ------------->| (in px)

      double ratio = 1./4;
      TPad *pad1 = new TPad("pad1", "title",
			    0.0, ratio ,  // xmin , ymin
			    1.0, 1.0 ,    // xmax , ymax
			    -1, -1, -2 );
      pad1->SetTopMargin( 125.0 / 1000 );
      pad1->SetBottomMargin( 0.0 );
      pad1->Draw();
      pad1->SetNumber(1);

      TPad *pad2 = new TPad("pad2", "title",
			    0.0 , 0.0,    // xmin , ymin
			    1.0 , ratio , // xmax , ymax
			    -1  , -1, -2 );

      pad2->SetTopMargin( 0.00 );
      pad2->SetBottomMargin( 80.0 / 250.0 );
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

