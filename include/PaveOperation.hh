#ifndef MYLIB_PAVEOPERATION_HH
#define MYLIB_PAVEOPERATION_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"

#ifndef __CINT__
/*!
  @fn void DrawTitle(TVirtualPad* pad)
  @param
  @return
  @brief
 */
void DrawTitle(TVirtualPad* pad);

/*!
  @fn void DrawTitle(TVirtualPad* pad, Double_t text_size = 0.07 )
  @param
  @return
  @brief
 */
void DrawTitle(TVirtualPad* pad, Double_t text_size = 0.07 );


/*!
  @fn void DrawTitle(Double_t text_size = 0.07 )
  @param
  @return
  @brief
 */
void DrawTitle(Double_t text_size = 0.07 );

/*!
  @fn void DrawTitle(Double_t text_size = 0.07 )
  @param
  @return
  @brief
 */
//void DrawTitle();

/*!
  @fn void DrawStats( TH1D* hist, double xmin, double ymin, double xmax, double ymax )
  @param
  @return
  @brief
 */

/*!
  @fn void DrawStats2D( TH2D* hist, double xmin, double ymin, double xmax, double ymax )
  @param
  @return
  @brief
 */
void DrawStats2D( TH2D* hist, double xmin, double ymin, double xmax, double ymax );

/*
void DrawTitle(TVirtualPad* pad)
{

  TPaveText* title = (TPaveText*)pad->GetPrimitive( "title" );
  //      frame->SetTitleSize( 0.09 );
  title->SetTextSize( 0.09 );
  title->SetTextAlign( 23 );
  title->Draw( "same" );
}

void DrawStats( TH1D* hist, double xmin, double ymin, double xmax, double ymax )
{

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
*/

#endif // __CINT__

#ifdef __CINT__
#include "../src/PaveOperation.cc"
#endif // __CINT__

template < typename TH >
void DrawStats( TH* hist, double xmin, double ymin, double xmax, double ymax )
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


#endif
