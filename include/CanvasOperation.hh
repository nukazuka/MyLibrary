#ifndef MYLIB_CANVASOPERATION_HH
#define MYLIB_CANVASOPERATION_HH

#include "HeadersRoot.hh"
#include <string>

using namespace std;
//TCanvas* GetCanvas( string name, string shape, bool logy=false );

/*!
  @fn TCanvas* GetCanvas( string name, string shape, bool logy )
  @param name a name of canvas
  @param shape see details
  @param logy log scale for y axis of not
  @brief get canvas
  @details ## Defined Shapes
  name       | width | height | ratio  | usage          | remarks
  ---------  | ----- | ------ | ------ | -------------- | -------- |
  square     | 1000  | 1000   | 1:1    | normal | |
  landscape  | 1200  |  800   | 1.5:1  | | |
  3:2        | 1200  |  800   | 1.5:1  | | |
  presen     |  255  |  170   | 1.5:1  | for presentation | |
  double     | 1600  |  800   | 2:1    | 2 graphs | |
  triple     | 2400  |  800   | 3:1    | 3 graphs | |
  quad       | 3200  |  800   | 4:1    | 4 graphs | |
  comparison | 1000  | 1450   | 1:1.45 | comparison | see below

  ### Comparison shape


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //    -------------------------
  //    |//////// title /////// |  100   
  //    |                       |       
  //    |                       |       
  //    |           #1          | 
  //    |         Hists         | 1000
  //    |                       |
  //    |                       |
  //    |-----------------------|
  //    |           #2          |
  //    |         Ratio         |  250
  //    |                       |  
  //    |///// axis title //////|  100
  //    -------------------------
  //    <--------- 1000 -------->
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
