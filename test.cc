#define __CINT__

#ifdef __linux__
#include "/home/gnukazuk/local/MyLibrary/include/MyLibrary.hh"
#elif __APPLE__
#include "/Users/nukazuka/local/MyLibrary/include/MyLibrary.hh"
#endif

int test()
{

  TCanvas* c = GetCanvas( "name", "square", false );
  TH1D* hist1 = new TH1D( "hist1", "title1", 2e3, -10, 10);
  TH1D* hist2 = new TH1D( "hist2", "title2", 2e3, -10, 10);

  SetHistStyle( hist1, kBlack, 2 );
  SetHistStyle( hist2, kRed, 2 );


  TRandom3* rand = new TRandom3();
  for( int i=0; i<1e6; i++ )
    {
      hist1->Fill( rand->Gaus( ) );
      hist2->Fill( rand->Gaus( 1, 2 ) );
    }

  MultiHist* mh = new MultiHist( "name", "title;title x; title y" );
  mh->SetYmin( 0 );
  mh->SetLabelSizeY( 0.03 );
  //  mh->SetTitleOffsetY( 1.25 );
  mh->SetTitleOffsetY( 0);
  mh->SetStatsBoxSize( 0.1, 0.15 );
  mh->SetStatsBoxPoint( 0.7, 0.8 );
  mh->Add( hist1 );
  mh->Add( hist2 );

  mh->Draw();
  //  c->Print( "sample.svg" );
  return 1;

}
