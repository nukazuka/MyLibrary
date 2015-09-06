#include "GetCanvas.hh"
using namespace std;

TCanvas* GetCanvas( string name, string title, bool logy )
{

  TCanvas* c = new TCanvas( name.c_str(), title.c_str(), 1200, 800 );
  c->SetLogy( logy );

  CanvasSetting(c);
  return c;
}

