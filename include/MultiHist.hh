#ifndef MYLIB_MULTIHIST_HH
#define MYLIB_MULTIHIST_HH

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include "PaveOperation.hh"

/*!
  @class MultiHist
  @brief This class treats multi-histograms.
  @date 26/Nov./2015
  @author G. Nukazuka
  @detail This can make a frame which all histograms are in.
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
  
  vector < TH1D* > vhist;

  // Initialization
  void Init( string name, string title );
  void GetRanges();
  
public:

  // Constructor
  /*!
    @fn MultiHist()
    @brief A default constructor.
  */
  MultiHist(){ Init( "default_name", "default_title" ); } ;

  /*!
    @fn MultiHist( string name, string title)
    @param name A name of this object.
    @param title A title of this object
    @brief A constructor with name and title
  */
  MultiHist( string name, string title ){ Init( name, title) ;} ;

  // void 
  /*!
    @fn void Add( TH* hist )
    @param hist A pointer of histogram which you want to treat.
    @brief Add the histogram to this class
  */
  void Add( TH1* hist );

  void Draw( string option );
    
  void Draw( string option,
	     double stats_xmin, double stats_ymin,
	     double stats_xmax, double stats_ymax );
  
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
    @brief
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
