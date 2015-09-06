#ifndef CanvasSetting_hh
#define CanvasSetting_hh

#include "TROOT.h"
#include "TPad.h"
#include "TStyle.h"

#ifndef __CINT__
void PadSetting();
void CanvasSetting();
void CanvasSetting( TCanvas* c );
#endif

#ifdef __CINT__
#include "../src/CanvasSetting.cc"
#endif // __CINT__

#endif //CanvasSetting_hh
