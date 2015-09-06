#ifndef MYLIB_CANVASOPERATION_HH
#define MYLIB_CANVASOPERATION_HH

#include "HeadersRoot.hh"
#include <string>

using namespace std;
//TCanvas* GetCanvas( string name, string shape, bool logy=false );
TCanvas* GetCanvas( string name, string shape, bool logy );
void PadSetting();
void CanvasSetting();
void CanvasSetting( TCanvas* c);

#endif
