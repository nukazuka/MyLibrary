#ifndef __CINT__
#include "PaveOperation.hh"
#endif

using namespace std;
void DrawTitle(TVirtualPad* pad)
{
  DrawTitle( pad , 0.09 );
}

void DrawTitle(TVirtualPad* pad, Double_t text_size )
{

  gPad->Update();

  TPaveText* title = (TPaveText*)pad->GetPrimitive( "title" );
  //      frame->SetTitleSize( 0.09 );
  title->SetTextSize( text_size );
  title->SetTextAlign( 23 );
  title->Draw( "same" );
}

void DrawStats( TH1D* hist, double xmin, double ymin, double xmax, double ymax )
{

  gPad->Update();

  TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
  st->SetTextColor( hist->GetLineColor() );
  st->SetLineColor( hist->GetLineColor() );
  st->SetFillStyle( 1001 );
  st->SetFillColor( 0 );

  st->SetX1NDC( xmin );
  st->SetX2NDC( xmax );
  st->SetY1NDC( ymin );
  st->SetY2NDC( ymax );

  //  st->SetOptStat( 111111 ) ; // overflow and underflos are ON
  st->Draw("same");
}

void DrawStats2D( TH2D* hist, double xmin, double ymin, double xmax, double ymax )
{

  gPad->Update();

  TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
  st->SetTextColor( hist->GetLineColor() );
  st->SetLineColor( hist->GetLineColor() );
  st->SetFillStyle( 1001 );
  st->SetFillColor( 0 );

  st->SetX1NDC( xmin );
  st->SetX2NDC( xmax );
  st->SetY1NDC( ymin );
  st->SetY2NDC( ymax );

  st->Draw("same");
}
