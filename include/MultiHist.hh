#ifndef MYLIB_MULTIHIST_HH
#define MYLIB_MULTIHIST_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "PaveOperation.hh"
#include "StringOperation.hh"

/*!
  @class MultiHist
  @brief This class treats multi-histograms.
  @date 26/Nov./2015
  @author G. Nukazuka
  @details This class handle some histograms at same time.
  @todo # クラスに付け加えるもの
  - 統計情報の位置指定をできるようにする。
  - draw_no_entry を実装する（ソースの Ranges() not ready の箇所）
*/

using namespace std;

class MultiHist
{
private:

  int id_;
  int stats_type_;
  string name_;
  string title_;
  string option_;

  double xmin_;
  double xmax_;
  double ymin_;
  double ymax_;

  double xmin_force_;
  double ymin_force_;
  double xmax_force_;
  double ymax_force_;

  double margin_ratio_top_;
  double margin_ratio_right_;
  double margin_ratio_bottom_;
  double margin_ratio_left_;

  double stats_xmin_;
  double stats_ymin_;
  double stats_xmax_;
  double stats_ymax_;

  double offset_title_x_;
  double offset_title_y_;

  double stats_width_;
  double stats_height_;

  double title_size_;

  bool bl_stats_;
  bool bl_title_;
  bool bl_draw_no_entry_;
  bool bl_force_xmin_;
  bool bl_force_xmax_;
  bool bl_force_ymin_;
  bool bl_force_ymax_;
  bool bl_logx_;
  bool bl_logy_;
  
  vector < TH1D* > vhist_;

  // Initialization
  void Init( );
  void Init( string name, string title );
  void CheckLogScale();
  void Margins();
  void Ranges();
  double GetSuitableXmin();
  double GetSuitableYmin();
  
public:

  // Constructor
  /*!
    @fn MultiHist()
    @brief A default constructor.
  */
  MultiHist(){ Init();};

  /*!
    @fn MultiHist( string name, string title)
    @param name A name of this object.
    @param title A title of this object
    @brief A constructor with name and title
  */
  MultiHist( string name, string title ){ Init( name, title) ;} ;

  // void 
  /*!
    @fn void Add( TH1* hist )
    @param hist A pointer of histogram which you want to treat.
    @brief Add the histogram to this class
    @details The argument is a pointer of TH1 but casted to TH1D*.
    This conversion does not lose information.
  */
  void Add( TH1* hist );

  /*!
    @fn void DeleteAllHist()
    @brief All added histograms are deleted
  */
  void DeleteAllHist();

  /*!
    @fn void Draw( string option )
    @param option An option for TH1D::Draw
    @brief Draw all histograms.
    @details Statistic boxies are drawn with soecified type.
    If you want to use "box" type, use this function.
  */
  void Draw( string option = "" );

  /*!
    @fn   void Draw( string option, double stats_xmin, double stats_ymin, double stats_xmax, double stats_ymax )
    @param option options for drawing.
    @param stats_xmin
    @param stats_ymin
    @param stats_xmax
    @param stats_ymax
    @brief draw all histograms which had been stored
    @details if scale of x and/or y are set to log scale and minimum values are negative, ranges will be modified automatically.
  */
  void Draw( string option,
	     double stats_xmin, double stats_ymin,
	     double stats_xmax, double stats_ymax );
  
  /*!
    @ void SetOption( string option )
    @param option options for drawing
    @brief set options for drawing
  */
  void SetOption( string option ){ option_ = option;};

  /*!
    @fn void SetMarginTop( double ratio )
    @param ratio ratio of margin
    @brief Set margin in %
  */
  void SetMarginTop( double ratio ){ margin_ratio_top_ = ratio;};

  /*! 
    @fn void SetMarginRight( double ratio )
    @param ratio
    @brief set right margin in %
   */
  void SetMarginRight( double ratio ){ margin_ratio_right_ = ratio;};

  /*!
    @fn void SetMarginBottom( double ratio )
    @param ratio ratio of margin
    @brief Set margin in %
  */
  void SetMarginBottom( double ratio ){ margin_ratio_bottom_ = ratio;};

  /*!  
    @fn void SetMarginLeft( double ratio )
    @param ratio ratio of margin
    @brief
  */
  void SetMarginLeft( double ratio ){ margin_ratio_left_ = ratio;};

  /*!  
    @fn void SetMarginV( double ratio )
    @param ratio ratio of margin
    @brief Set margin in %
  */
  void SetMarginV( double ratio );

  /*!
    @fn void SetMarginH( double ratio )
    @param ratio
    @brief
  */
  void SetMarginH( double ratio );

  /*!
    @fn void SetMargins( double ratio )
    @param ratio
    @brief
  */
  void SetMargins( double ratio );

  /*!
    @fn void SetStatsPosition( double xmin, double ymin, double xmax, double ymax )
    @param xmin a position of left side of stats in ratio
    @param ymin a position of bottom of stats in ratio
    @param xmax a position of right side of stats in ratio
    @param ymax a position of top side of stats in ratio
    @brief set position of box for statistic
    @details all values are in ratio
  */
  void SetStatsPosition( double xmin, double ymin, double xmax, double ymax );

  /*!
    @fn void SetStatsBoxSize( double width , double height )
    @param width
    @param height
    @brief set size of stats box
    @detail This function is for "box" type arrangement.
  */
  void SetStatsBoxSize( double width , double height );

  /*!
    @fn void SetStatsBoxPoint( double xmax , double ymax )
    @param xmax right side of stats box
    @param ymax bottom side of stats box
    @brief set point 
    @details 
  */
  void SetStatsBoxPoint( double xmax , double ymax );

  /*!
    @fn void SetStatsType( string type )
    @param type type of an arrengement of stats box
    @brief set an arrangement type of stats box
    @details following types are supported
    - area, Area, AREA : you can specify are of stats with void SetStatsPosition( double xmin, double ymin, double xmax, double ymax ). The area will be devided into a number of hist and stats boxes will be drawn in specified direction.
  */
  void SetStatsType( string type );

  /*!
    @fn void SetStatsType( int num )
    @param num an arrangement of stats box 
    @brief set type of stats box with int
    @details user should use void MultiHist::SetStatsType( string type )
  */
  void SetStatsType( int num ){ stats_type_ = num ;};

  /*!
    @fn void SetDrawNoEntry ( bool bl )
    @param
    @brief
    @details
  */
  void SetDrawNoEntry ( bool bl )     { bl_draw_no_entry_ = bl ;};

  /*!
    @fn void SetStats( bool bl )
    @param
    @brief
    @details
  */
  void SetStats       ( bool bl )     { bl_stats_ = bl;};

  /*!
    @fn void SetTitleDraw ( bool bl )
    @param title new title
    @brief set title
  */
  void SetTitle   ( string title )     { title_ = title;};

  void SetTitleOffsetX( double offset ){ offset_title_x_ = offset;};
  void SetTitleOffsetY( double offset ){ offset_title_y_ = offset;};

  /*!
    @fn void SetTitleDraw ( bool bl )
    @param bl Title will be drawn if bl == true,
    @brief Set whether draw title or not
  */
  void SetTitleDraw   ( bool bl )     { bl_title_ = bl;};

  /*!
    @fn void SetTitleSize( double size )
    @param
    @brief
    @details
  */
  void SetTitleSize   ( double size ) { title_size_ = size;};

  /*!
    @fn void SetXmin( double val )
    @param
    @brief
    @details
  */
  void SetXmin( double val );

  /*!
    @fn void SetXmax( double val )
    @param
    @brief
    @details
  */
  void SetXmax( double val );
  /*!
    @fn void SetYmin( double val )
    @param
    @brief
    @details
  */
  void SetYmin( double val );
  /*!
    @fn void SetYmax( double val )
    @param
    @brief
    @details
  */
  void SetYmax( double val );
  
  /*!
    @fn void Print()
    @brief
    @details
  */
  void Print();

  // int 
  //  int Get

  // string 
  /*!
    @fn string GetName()
    @param
    @brief
    @details
  */

  string GetName(){ return name_;};
  /*!
    @fn string GetTitle()
    @brief return the title of this object
  */
  string GetTitle(){ return title_;};

};

#endif
