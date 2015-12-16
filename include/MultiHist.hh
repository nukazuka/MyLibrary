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
*/

using namespace std;

class MultiHist
{
private:
  string name_;
  string title_;
  string option_;

  double xmin_;
  double xmax_;
  double ymin_;
  double ymax_;
  double margin_ratio_top_;
  double margin_ratio_right_;
  double margin_ratio_bottom_;
  double margin_ratio_left_;
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
    @fn void Draw( string option )
    @param option An option for TH1D::Draw
    @brief Draw all histograms.
    @details Statistic boxies are drawn in right side of the frame.
  */
  void Draw( string option );

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

  void SetDrawNoEntry ( bool bl )     { bl_draw_no_entry_ = bl ;};
  void SetStats       ( bool bl )     { bl_stats_ = bl;};
  void SetTitleDraw   ( bool bl )     { bl_title_ = bl;};
  void SetTitleSize   ( double size ) { title_size_ = size;};

  void SetXmin( double val );
  void SetXmax( double val );
  void SetYmin( double val );
  void SetYmax( double val );
  
  void Print();

  // int 
  //  int Get

  // string 
  string GetName(){ return name_;};
  string GetTitle(){ return title_;};

};

#endif
