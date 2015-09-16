#ifndef GETCANVAS_HH
#define GETCANVAS_HH

#ifdef __APPLE__
#include "/Users/nukazuka/cernbox/share/ROOT/include/CanvasSetting.hh"
#endif //__APPLE__

#ifdef __linux__
#include "/home/gnukazuk/cernbox/share/ROOT/include/CanvasSetting.hh"
#endif //__linux__

#include "HeadersRoot.hh"

#include <string>

using namespace std;
TCanvas* GetCanvas( string name, string title, bool logy=false );
#endif
