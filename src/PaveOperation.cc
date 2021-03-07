#ifndef MYLIB_PAVEOPERATION_CC
#define MYLIB_PAVEOPERATION_CC
#ifndef __CINT__
#include "PaveOperation.hh"
#endif

using namespace std;


void DrawTitle(TVirtualPad* pad, Double_t text_size , int text_align, int font )
{

  pad->Update();

  TPaveText* title = (TPaveText*)pad->GetPrimitive( "title" );

  if( text_size < 0 )
    text_size = 0;

  title->SetTextSize( text_size );
  title->SetTextAlign( text_align );
  //  title->SetTextFont( font );
  title->Draw( "same" );
}

void DrawTitle( Double_t text_size , int text_align, int font )
{
  DrawTitle( gPad , text_size , text_align, font );
}

void DrawTitle(TVirtualPad* pad, Double_t text_size )
{
  DrawTitle( pad , text_size , 23, 4);
}

void DrawTitle(TVirtualPad* pad)
{
  DrawTitle( pad , 0.07 , 23, 4);
}

/*
void DrawTitle()
{
  DrawTitle( gPad , 0.07);
}
*/

//void DrawPaletteAxis( TH2D* hist , 
TPaletteAxis* DrawPaletteAxis( TH2D* hist , 
		      double xmin, double ymin,
		      double xmax, double ymax ,
		      double label_size)
{

  gPad->Update();
  TPaletteAxis *pal = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
  pal->GetAxis()->SetLabelSize( label_size );
  pal->GetAxis()->CenterTitle();

  pal->SetX1NDC( xmin );
  pal->SetX2NDC( xmax );

  pal->SetY1NDC( ymin );
  pal->SetY2NDC( ymax );
  pal->Draw();

  return pal;
}

/*
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
*/
// void DrawStats2D( TH2D* hist, double xmin, double ymin, double xmax, double ymax )
// {
//   DrawStats<TH2D>( hist, xmin, ymin, xmax, ymax );
// }

#endif // MYLIB_PAVEOPERATION_CC
