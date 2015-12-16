#ifndef CanvasSetting_hh
#define CanvasSetting_hh

#include "TROOT.h"
#include "TPad.h"
#include "TStyle.h"

#ifndef __CINT__
/*!
  @fn void PadSetting();
  @param
  @return
  @brief
 */
void PadSetting();

/*!
  @fn void CanvasSetting();
  @param
  @return
  @brief
 */
void CanvasSetting();

/*!
  @fn void CanvasSetting( TCanvas* c );
  @param
  @return
  @brief
 */
void CanvasSetting( TCanvas* c );
#endif

//#ifdef __CINT__
//#include "../src/CanvasSetting.cc"
//#endif // __CINT__

#endif //CanvasSetting_hh
