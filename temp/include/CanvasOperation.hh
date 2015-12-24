#ifndef MYLIB_CANVASOPERATION_HH
#define MYLIB_CANVASOPERATION_HH

#include "HeadersRoot.hh"
#include <string>

using namespace std;
//TCanvas* GetCanvas( string name, string shape, bool logy=false );

/*!
  @fn TCanvas* GetCanvas( string name, string shape, bool logy )
  @param
  @return
  @brief
 */
TCanvas* GetCanvas( string name, string shape, bool logy );

/*!
  @fn void PadSetting()
  @param
  @return
  @brief
 */
void PadSetting();

/*!
  @fn void CanvasSetting()
  @param
  @return
  @brief
 */
void CanvasSetting();

/*!
  @fn void CanvasSetting( TCanvas* c)
  @param
  @return
  @brief
 */
void CanvasSetting( TCanvas* c);

#endif
