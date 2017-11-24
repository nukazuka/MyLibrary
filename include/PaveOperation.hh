#ifndef MYLIB_PAVEOPERATION_HH
#define MYLIB_PAVEOPERATION_HH

#include "TPaletteAxis.h"
#include "HeadersSL.hh"
#include "HeadersRoot.hh"

#ifndef __CINT__

/*!
  @fn void DrawTitle(TVirtualPad* pad, Double_t text_size , int text_align )
  @param pad 対象となる pad 
  @param test_size text size
  @param text_align 文字の置き方
  @brief pad にある title オブジェクトを取得して書き直す
  @details 他の DrawTitle は最終的にこの関数を呼び出している。
*/
void DrawTitle(TVirtualPad* pad, Double_t text_size , int text_align, int font = 4 );

/*!
  @fn void void DrawTitle( Double_t text_size = 0.07 , int test_align = 23 )
  @param
  @param
  @brief
  @details
*/
void DrawTitle( Double_t text_size = 0.07 , int test_align = 23, int font = 4 );

/*!
  @fn void DrawTitle(TVirtualPad* pad, Double_t text_size = 0.07 )
  @brief
  @details 後方互換性のために残してるけど，もう使わない。
 */
void DrawTitle(TVirtualPad* pad, Double_t text_size = 0.07 );

/*!
  @fn void DrawTitle(TVirtualPad* pad)
  @param
  @return
  @brief
 */
void DrawTitle(TVirtualPad* pad);


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
//void DrawStats2D( TH2D* hist, double xmin, double ymin, double xmax, double ymax );

/*!
  @fn void DrawPaletteAxis( TH2D* hist , double xmin = 0.9 , double ymin = 0.1, double xmax = 0.93, double ymax = 0.9, double label_size = 0.08 )
  @param hist target of histogram
  @param xmin left position in ratio
  @param ymin bottom position in ratio
  @param xmax right position in ratio
  @param ymax top position in ratio
  @param label_size size of label
  @brief Draw color palette axis for TH2
  @details

*/
void DrawPaletteAxis( TH2D* hist = new TH2D(), 
		      double xmin = 0.9 , double ymin = 0.1,
		      double xmax = 0.93, double ymax = 0.9,
		      double label_size = 0.08 );

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


// template < typename TH >
// void DrawStats( TH* hist, double xmin, double ymin, double xmax, double ymax )
// {
//   DrawStats<TH>( hist, xmin, ymin, xmax, ymax , 4 );
// }

template < typename TH >
//void DrawStats( TH* hist, double xmin, double ymin, double xmax, double ymax )
void DrawStats( TH* hist, double xmin, double ymin, double xmax, double ymax, int font = 4)
{

  gPad->Update();

  TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
  st->SetTextColor( hist->GetLineColor() );
  st->SetLineColor( hist->GetLineColor() );
  st->SetFillStyle( 1001 );
  st->SetFillColor( 0 );
  st->SetTextFont( font );
  
  st->SetX1NDC( xmin );
  st->SetX2NDC( xmax );
  st->SetY1NDC( ymin );
  st->SetY2NDC( ymax );

  //  st->SetOptStat( 111111 ) ; // overflow and underflos are ON
  st->Draw("same");
}

#ifdef __CINT__
#include "../src/PaveOperation.cc"
#endif

#endif
