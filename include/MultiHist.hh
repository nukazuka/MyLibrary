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

  static int id_;
  int stats_type_ = 1;
  string name_;
  string title_;
  string option_;

  // min and max value of x and y axis
  double xmin_ = 1.0;
  double xmax_ = 2.0;
  double ymin_ = 1.0;
  double ymax_ = 2.0;

  double xmin_force_ = -9999.9;
  double ymin_force_ = -9999.9;
  double xmax_force_ = -9999.9;
  double ymax_force_ = -9999.9;

  double margin_ratio_top_    = 0.1;
  double margin_ratio_right_  = 0.01;
  double margin_ratio_bottom_ = 0.01;
  double margin_ratio_left_   = 0.01;

  double margin_top_    = 10;
  double margin_right_  = 10;
  double margin_bottom_ = 10;
  double margin_left_   = 10;

  double stats_xmin_ = 0.9;
  double stats_ymin_ = 0.1;
  double stats_xmax_ = 1.0;
  double stats_ymax_ = 0.9;
  int    stats_font_ = 62;
  
  // valiable for axis' title
  string title_x_ = " ";
  string title_y_ = " ";
  double offset_title_x_ = 1.0;
  double offset_title_y_ = 1.0;
  double size_title_x_ = 0.04;
  double size_title_y_ = 0.04;

  // valiable for axis' label
  double offset_label_x_ = 0.005;
  double offset_label_y_ = 0.005;
  double size_label_x_   = 0.04;
  double size_label_y_   = 0.04;

  int division_x_ = 510;
  int division_y_ = 510;

  // valiable for stats box
  //  int    stats_format_ = 1000111; // name, mean, std.dev., integral
  int    stats_format_ = 111; // name, mean, std.dev., integral
  double stats_width_  = 0.1;
  double stats_height_ = 0.1;

  // valiable for title 
  double title_size_ = 0.07;
  int title_align_ = 23;

  bool bl_stats_		= true;
  bool bl_title_		= true;
  bool bl_draw_no_entry_	= false;
  bool bl_force_xmin_		= false;
  bool bl_force_xmax_		= false;
  bool bl_force_ymin_		= false;
  bool bl_force_ymax_		= false;
  bool bl_logx_			= false;
  bool bl_logy_			= false;
  bool bl_draw_palette_axis_	= true;
  bool bl_ratio_mode_		= false;
  bool bl_include_error_bar_	= true;
  bool bl_ratio_normalize_	= true;
  
  vector < TH1D* > vhist_;
  vector < TH2D* > vhist2d_;
  TH1D* hist_base_;
  
  // Initialization
  void Init( );
  void Init( string name, string title );
  void CheckLogScale();
  void FrameSetting( TH1F* frame, double margin_bottom, double margin_top );
  double GetHistEnd( TH1D* hist );
  double GetHistStart( TH1D* hist );

  /*!

    @fn double GetMinimumBin_Non0( int hist_id )
    @brief return the min. value except 0 from specified hist
  */
  double GetMinimumBin_Non0( int hist_id );

  double GetMaximumBin_Non0( int hist_id );
  double GetSuitableXmin();
  double GetSuitableYmin();
  void Margins();
  void Ranges();
  void Ranges2D();
  double GetMaxError();

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

  /*!
    @fn MultiHist( string name, string title)
    @param name A name of this object.
    @param title A title of this object
    @param vhist hists to be drawn
    @brief A constructor with name and title. Given hists will be added.
  */
  MultiHist( string name, string title , vector < TH1D* > vhist );

  /*!
    @fn MultiHist( string name, string title , TH1D* hist_base , TH1D* hist_divide_with )
    @param name A name of this object.
    @param title A title of this object
    @param hist_base this hist is divided by 4th argument
    @param hist_divide_with 
    @param bl_normalize a flag of normalization
    @brief A constructor for ratio mode. hists are normalized before division
  */
  MultiHist( string name, string title , TH1D* hist_base , TH1D* hist_divide_with , bool bl_normalize = true );

  /*!
    @fn MultiHist( string name, string title , TH1D* hist_base , TH1D* hist_divide_with )
    @param name A name of this object.
    @param title A title of this object
    @param hist_base this hist is divided by 4th argument
    @param hist_divide_with 
    @brief A constructor for ratio mode. hists are normalized before division
  */
  //  MultiHist( string name, string title , TH1D* hist_base , TH1D* hist_divide_with );

  // void 
  /*!
    @fn void Add( TH1* hist )
    @param hist A pointer of histogram which you want to treat.
    @brief Add the histogram to this class
    @details The argument is a pointer of TH1 but casted to TH1D*.
    This conversion does not lose information.
  */
  void Add( TH1* hist );
  //void Add( TH1D* hist );

  /*!
    @fn void Add( TH2D* hist2d )
    @param hist2d A pointer of 2 dimensional histogram
    @brief add 2D histogram
    @details If at least one 2D hist have been added, 1D hist will not be drawn.
    To remove 2D hists, use DeleteHist2D().
  */
  void Add( TH2D* hist2d );

  /*!
    @fn void AddBaseHist( TH1D* hist_base )
    @brief add base hist of ratio mode
  */
  void AddBaseHist( TH1D* hist_base );


  /*!
    @fn void CopySetting( MultiHist* mh )
  */
  void CopySetting( MultiHist* mh );
  
  /*!
    @fn void DeleteAllHist()
    @brief Delete all stored histograms
  */
  void DeleteAllHist();

  /*!
    @fn void DeleteHist()
    @brief Delete stored 1D histograms 
  */
  void DeleteHist();

  /*!
    @fn void DeleteHist2D()
    @brief Delete stored 2D histograms
  */
  void DeleteHist2D();

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

  void DrawWithoutFrame( string option = "" );

  void DrawWithoutFrame( string option,
			 double stats_xmin, double stats_ymin,
			 double stats_xmax, double stats_ymax );
  
  /*!
    @fn void DrawFrame()
    @brief Draw only frame
  */
  //  void DrawFrame();
  TH1F* DrawFrame( string option = "0" );

  /*!
    @fn void Draw2D( string option )
    @param option An option for TH2D::Draw
    @brief Draw all 2D histograms
  */
  void Draw2D( string option = "" );

  /*!
    @fn   void Draw2D( string option, double stats_xmin, double stats_ymin, double stats_xmax, double stats_ymax )
    @param option An option for TH2D::Draw
    @brief Draw all 2D histograms
  */
  void Draw2D( string option,
	       double stats_xmin, double stats_ymin,
	       double stats_xmax, double stats_ymax );


  string GetTitleX()		{ return title_x_ ;		};
  string GetTitleY()		{ return title_y_ ;		};
  double GetTitleOffsetX()	{ return offset_title_x_ ;	};
  double GetTitleOffsetY()	{ return offset_title_y_ ;	};
  double GetTitleSizeX()	{ return size_title_x_ ;	};
  double GetTitleSizeY()	{ return size_title_y_ ;	};
  double GetLabelOffsetX()	{ return offset_label_x_ ;	};
  double GetLabelOffsetY()	{ return offset_label_y_ ;	};
  double GetLabelSizeX()	{ return size_label_x_   ;	};
  double GetLabelSizeY()	{ return size_label_y_   ;	};
  int    GetDivisionX()		{ return division_x_ ;		};
  int    GetDivisionY()		{ return division_y_ ;		};
  int    GetStatsFormat()	{ return stats_format_ ;	};
  double GetStatsWidth()	{ return stats_width_  ;	};
  double GetStatsHeight()	{ return stats_height_ ;	};
  double GetTitleSize()		{ return title_size_ ;		};
  int    GetTitleAlign()	{ return title_align_ ;		};


  
  /*!
    @fn int GetEntries()
    @brief get entires of hist
  */
  int GetEntries(){ return vhist_.size();} ;

  /*!
    @fn int Get2DEntries()
    @brief get entires of 2D hist
  */
  int Get2DEntries(){ return vhist2d_.size();} ;

  /*!
    @fn int GetEntries()
    @brief get entires of 1D hist and 2D hist
  */
  int GetAllEntries(){ return GetEntries() + Get2DEntries() ;} ;

  /*!
    TH1D* GetHist( int num );
    @brief the 1D hist stored in num-th is returned
  */
  TH1D* GetHist( int num );

  /*!
    @fn TH2D* GetHist2D( int num );
    @brief the 2D hist stored in num-th is returned
  */
  TH2D* GetHist2D( int num );
  
  /*!
    @fn vector < TH1D* > GetHists()
    @brief all 1D hists are returned
  */
  vector < TH1D* > GetHists(){ return vhist_;};

  /*!
    @fn vector < TH1D* > GetHists2D()
    @brief all 2D hists are returned
  */
  vector < TH2D* > GetHists2D(){ return vhist2d_;};

  /*!
    @fn string GetName()
    @brief get the name of this object
  */
  string GetName(){ return name_;};

  /*!
    @fn string GetTitle()
    @brief return the title of this object
  */
  string GetTitle(){ return title_;};

  /*!
    @fn   bool GetRatioMode()
    @brief check whether this is ratio mode or not
  */
  bool GetRatioMode(){ return bl_ratio_mode_;};

  /*!
    @fn double GetXmax()
    @brief Get max. range of x axis
  */
  //  double GetXmax(){ return xmax_ + margin_right_ ;};
  double GetXmax();

  /*!
    @fn double GetXmin()
    @brief Get min. range of x axis
  */
  //  double GetXmin(){ return xmin_ - margin_left_ ;};
  double GetXmin();

  /*!
    @fn double GetYmax()
    @brief Get max. range of y axis
  */
  //  double GetYmax(){ return ymax_ + margin_top_ ;};
  double GetYmax();

  /*!
    @fn double GetYmin()
    @brief Get max. range of y axis
  */
  //  double GetYmin(){ return ymin_ - margin_bottom_ ;};
  double GetYmin();

  /*!
    @fn   bool IsRatioMode()
    @brief same as GetRatioMode
  */
  bool IsRatioMode(){ return bl_ratio_mode_;};
  
  /*!
    @fn void NormalizeHist( double val = 1.0 )
    @brief all stored hists are normalized to val
  */
  void NormalizeHist( double val = 1.0 );
  
  /*!
    @fn void Print()
    @brief
    @details
  */
  void Print();

  /*!
    @void void ResetRange()
    @brief all specified range are reset
  */
  void ResetRange();

  /*!
    @fn void SetDivisionX( int div = 510 )
    @param div see [TAttAxis][https://root.cern.ch/doc/master/classTAttAxis.html#ae3067b6d4218970d09418291cbd84084]
    @brief set the number of division for this axis.
  */
  void SetDivisionX( int div ){ division_x_ = div;};

  /*!
    @fn void SetDivisionY( int div = 510 )
    @param div see [TAttAxis][https://root.cern.ch/doc/master/classTAttAxis.html#ae3067b6d4218970d09418291cbd84084]
    @brief set the number of division for this axis.
  */
  void SetDivisionY( int div ){ division_y_ = div;};

  /*!
    @fn void SetDrawPaletteAxis( bool bl )
    @param bl draw palette axis or not
    @brief sed palette axis on or off
  */
  void SetDrawPaletteAxis( bool bl ){ bl_draw_palette_axis_ = bl;};

  /*!
    @fn void SetDrawNoEntry ( bool bl )
    @param
    @brief
    @details
  */
  void SetDrawNoEntry ( bool bl = true )     { bl_draw_no_entry_ = bl ;};

  /*!
    @fn void SetFont( int font_num )
    @brief set fonts for all
  */
  void SetFont( int font_num )
  {
    stats_font_ = font_num;
  }
  
  /*!
    @fn void SetIncludeErrorBar( bool bl = true )
    @brief range of y is adjusted to show all error bars or not
  */
  void SetIncludeErrorBar( bool bl = true ) { bl_include_error_bar_ = bl;};

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
    @fn void SetMarginRight( double ratio )
    @param ratio
    @brief set right margin in %
   */
  void SetMarginRight( double ratio ){ margin_ratio_right_ = ratio;};

  /*!
    @fn void SetMarginTop( double ratio )
    @param ratio ratio of margin
    @brief Set margin in %
  */
  void SetMarginTop( double ratio ){ margin_ratio_top_ = ratio;};

  /*!
    @fn void SetMarginH( double ratio )
    @param ratio
    @brief set horizontal margins in %
  */
  void SetMarginH( double ratio );

  /*!  
    @fn void SetMarginV( double ratio )
    @param ratio ratio of margin
    @brief Set margin in %
  */
  void SetMarginV( double ratio );

  /*!
    @fn void SetMargins( double ratio )
    @param ratio
    @brief set all margins in %
  */
  void SetMargins( double ratio );
  
  /*!
    @ void SetOption( string option )
    @param option options for drawing
    @brief set options for drawing
  */
  void SetOption( string option ){ option_ = option;};

  /*!
    @fn void SetRange( double xmin, double ymin, double xmax, double ymax )
    @brief set ranges to be drawn
  */
  void SetRange( double xmin, double ymin, double xmax, double ymax );


  /*!
    @fn void SetRatioMode( bool bl_mode )
    @brief set ratio mode
  */
  //  void SetRatioMode( bool bl_mode ){  bl_ratio_mode_ = bl_mode; bl_include_error_bar_ = true; };
  void SetRatioNormalize( bool bl = true ){  bl_ratio_normalize_  = bl;};

  /*!
    @fn void SetRatioMode( bool bl_mode )
    @brief set ratio mode
  */
  //  void SetRatioMode( bool bl_mode ){  bl_ratio_mode_ = bl_mode; bl_include_error_bar_ = true; };
  void SetRatioMode( bool bl_mode = true ){  bl_ratio_mode_ = bl_mode;};

  /*!
    @fn void SetStats( bool bl )
    @param bl flag
    @brief set whether stats box is on or off
  */
  void SetStats       ( bool bl )     { bl_stats_ = bl;};

  /*!
    @fn void SetStatsBoxSize( double width , double height )
    @param width
    @param height
    @brief set size of stats box
    @details This function is for "box" type arrangement.
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
    @fn void SetStatsFormat( int type )
    @param type format of stats box. 
    @brief Set format of stats box.
    @details see [here](https://root.cern.ch/doc/master/classTStyle.html#a0ae6f6044b6d7a32756d7e98bb210d6c) for format.    
  */
  void SetStatsFormat( int type );

  /*!
    @fn void SetStatsFormat( string type )
    @param type format of stats box. 
    @brief Set format of stats box.
    @details see [here](https://root.cern.ch/doc/master/classTStyle.html#a0ae6f6044b6d7a32756d7e98bb210d6c) for format.    
    @todo conversion fron string to int
  */
  void SetStatsFormat( string type );

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
    @fn void SetTitleDraw ( bool bl )
    @param title new title
    @brief set title
  */
  void SetTitle   ( string title )     { title_ = title;};

  /*!
    @fn void SetTitleAlign( int align )
    @param align align for title
    @brief see [here][https://root.cern.ch/doc/master/classTAttText.html#T1] for alignment
    @details
  */
  void SetTitleAlign   ( int align ) { title_align_ = align;};

  /*!
    @fn void SetTitleDraw ( bool bl )
    @param bool bl Title will be drawn if bl == true,
    @brief Set whether draw title or not
  */
  void SetTitleDraw   ( bool bl )     { bl_title_ = bl;};

  /*!
    @fn   void SetTitleX( string title )
    @param title title of x axis
    @brief set title of x axis
  */
  void SetTitleX( string title ){ title_x_ = title;};

  /*!
    @fn   void SetTitleY( string title )
    @param title title of y axis
    @brief set title of y axis
  */
  void SetTitleY( string title ){ title_y_ = title;};

  /*!
    @fn void SetLabelOffsetX( double offset )
    @param offset An offset of label in x axis
  */
  void SetLabelOffsetX( double offset ){ offset_label_x_ = offset;};

  /*!
    @fn void SetLabelOffsetY( double offset )
    @param offset An offset of label in y axis
  */
  void SetLabelOffsetY( double offset ){ offset_label_y_ = offset;};

  /*!
    @fn   void SetLabelSizeX( double size )
    @param size a size of x axis' label
  */
  void SetLabelSizeX( double size ){ size_label_x_ = size;};

  /*!
    @fn   void SetLabelSizeY( double size )
    @param size a size of y axis' label
  */
  void SetLabelSizeY( double size ){ size_label_y_ = size;};

  /*!
    @fn void SetTitleOffsetX( double offset )
    @param offset An offset of title in x axis
  */
  void SetTitleOffsetX( double offset ){ offset_title_x_ = offset;};

  /*!
    @fn void SetTitleOffsetY( double offset )
    @param offset An offset of title in y axis
  */
  void SetTitleOffsetY( double offset ){ offset_title_y_ = offset;};

  /*!
    @fn void SetTitleSize( double size )
    @param
    @brief
    @details
  */
  void SetTitleSize   ( double size ) { title_size_ = size;};

  /*!
    @fn void SetTitleSizeX( double size )
    @param size a size of x axis' title
    @brief set a size of x axis's title
  */
  void SetTitleSizeX   ( double size ) { size_title_x_ = size;};

  /*!
    @fn void SetTitleSizey( double size )
    @param size a size of y axis' title
    @brief set a size of y axis's title
  */
  void SetTitleSizeY   ( double size ) { size_title_y_ = size;};

  /*!
    @fn void SetXmin( double val )
    @param val min. of xaxis
    @brief set min. value of xaxis
    @details left margin will be ignored
  */
  void SetXmin( double val );

  /*!
    @fn void SetXmax( double val )
    @param val max. of xaxis
    @brief set max. value of xaxis
    @details right margin will be ignored
  */
  void SetXmax( double val );

  /*!
    @fn void SetYmin( double val )
    @param val min. of yaxis
    @brief set min. value of yaxis
    @details bottom margin will be ignored
  */
  void SetYmin( double val );

  /*!
    @fn void SetYmax( double val )
    @param val max. of yaxis
    @brief set max. value of yaxis
    @details top margin will be ignored
  */
  void SetYmax( double val );
};

#ifdef __CINT__
#include "../src/MultiHist.cc"
#endif

#endif
