#include "MultiHist.hh"

using namespace std;

int MultiHist::id_;
////////////////////////////////////////////////////////////
// private functions ///////////////////////////////////////
////////////////////////////////////////////////////////////

// // Initialization
void MultiHist::Init( )
{
  Init( (string)"default_name", (string)"default_title" );
}
void MultiHist::Init( string name, string title )
{

  //  id_ = 
  stats_type_ = 1;
  name_  = name;
  title_ = title;

  gStyle->SetOptStat( stats_format_ );

  CheckLogScale();
}

void MultiHist::CheckLogScale()
{
  bl_logx_ = gPad->GetLogx();
  bl_logy_ = gPad->GetLogy();
}

void MultiHist::FrameSetting( TH1F* frame, double margin_bottom, double margin_top )
{

  frame->SetMinimum( ymin_ - margin_bottom );
  frame->SetMaximum( ymax_ + margin_top );
  frame->SetStats( false );

  frame->GetXaxis()->CenterTitle( true );
  frame->GetYaxis()->CenterTitle( true );

  frame->GetXaxis()->SetTitleOffset( offset_title_x_ );
  frame->GetYaxis()->SetTitleOffset( offset_title_y_ );

  frame->GetXaxis()->SetTitleSize( size_title_x_ );
  frame->GetYaxis()->SetTitleSize( size_title_y_ );

  frame->GetXaxis()->SetLabelOffset( offset_label_x_ );
  frame->GetYaxis()->SetLabelOffset( offset_label_y_ );

  frame->GetXaxis()->SetLabelSize( size_label_x_ );
  frame->GetYaxis()->SetLabelSize( size_label_y_ );


  if( (string)(frame->GetXaxis()->GetTitle()) == "" )
    frame->GetXaxis()->SetTitle( title_x_.c_str() );

  if( (string)(frame->GetYaxis()->GetTitle()) == "" )
    frame->GetYaxis()->SetTitle( title_y_.c_str() );

  frame->GetXaxis()->SetNdivisions( division_x_ );
  frame->GetYaxis()->SetNdivisions( division_y_ );
}

double MultiHist::GetHistEnd( TH1D* hist )
{

  double rtn = -1;
  for( int i=hist->GetNbinsX(); i>-1; i-- )
    {
      if( hist->GetBinContent( i ) != 0 )
	  return hist->GetBinCenter(i);
    }
  return rtn;
}

double MultiHist::GetHistStart( TH1D* hist )
{

  double rtn = -1;
  for( int i=1, itotal=hist->GetNbinsX()+1; i<itotal; i++ )
    {
      if( hist->GetBinContent( i ) != 0 )
	  return hist->GetBinCenter(i);
    }
  return rtn;
}

double MultiHist::GetSuitableXmin()
{

  double xmin_candidate = 0.0;
  vector < double > vxmin_candidate;
  for( int i=0, itotal=vhist_.size(); i<itotal; i++ )
    {
      
      for( int j=0, jtotal=vhist_[i]->GetXaxis()->GetNbins(); j<jtotal; j++ )
	{
	  xmin_candidate = vhist_[i]->GetBinCenter(j);
	  
	  if( xmin_candidate > 0 )
	    {
	      vxmin_candidate.push_back( xmin_candidate );
	      break;
	    }
	}
    }

  return *min_element( vxmin_candidate.begin(), vxmin_candidate.end() );
}

double MultiHist::GetSuitableYmin()
{

  vector < double > ymin_candidate;
  for( int i=0, itotal=vhist_.size(); i<itotal; i++ )
    {

      vector < double > vtemp;
      for( int j=0, jtotal = vhist_[i]->GetXaxis()->GetNbins(); j<jtotal; j++ )
	vtemp.push_back( vhist_[i]->GetBinContent(j) );

      sort( vtemp.begin(), vtemp.end());

      for( int j=0, jtotal=vtemp.size(); j<jtotal; j++ )
	{

	  if( vtemp[j] > 0 )
	    {

	      ymin_candidate.push_back( vtemp[j] );
	      break;
	    }
	}
    }

  double min = *min_element( ymin_candidate.begin(), ymin_candidate.end() );
  return min;
}

void MultiHist::Margins()
{

  //  margin_ratio_top_ = 0.01;

  double diff_x = xmax_ - xmin_;
  double diff_y = ymax_ - ymin_;

  if( bl_logx_ == true  && (xmin_ - diff_x * margin_ratio_left_ ) <= 0 )
    margin_ratio_left_ = xmin_ * 0.5 / diff_x;

  if( bl_logy_ == true  && (ymin_ - diff_y * margin_ratio_bottom_ ) <= 0 )
      margin_ratio_bottom_ = ymin_ * 0.5 / diff_y;

}

void MultiHist::Ranges()
{

  CheckLogScale();
  vector < double > x, y;
  for( int i=0; i<vhist_.size(); i++ )
    {

      int bin = vhist_[i]->GetXaxis()->GetNbins();
      double width = vhist_[i]->GetBinWidth(i);
	
      if( bl_draw_no_entry_ == false )
	{
	  x.push_back( vhist_[i]->GetBinCenter(0)   - width/2. );
	  x.push_back( vhist_[i]->GetBinCenter(bin) + width/2. );
	}
      else
	{
	  x.push_back( GetHistStart( vhist_[i] ) - width/2 );
	  x.push_back( GetHistEnd( vhist_[i] )   + width/2 );
	}
      
      y.push_back( vhist_[i]->GetBinContent( vhist_[i]->GetMinimumBin() ) );
      y.push_back( vhist_[i]->GetBinContent( vhist_[i]->GetMaximumBin() ) );

    }

  double xmin = *min_element( x.begin(), x.end() );
  double xmax = *max_element( x.begin(), x.end() );

  // case ( x <= 0 ?)
  // (min, max):
  //   1. (OK, OK) : no problem
  //   2. (NO, OK) : can be happen    -> get suitable min. value
  //   3. (OK, NO) : something wrong  -> exit program
  //   4. (NO, NO) : very rare case   -> force liner scale
  //

  if( bl_logx_ == true )
    {

      if( xmin <= 0.0 && xmax <= 0.0 )// case4
	{

	  xmin_ = xmin;
	  xmax_ = xmax;
	  gPad->SetLogx( false );
	}
      else if( xmin > 0.0 && xmax <= 0.0 ) // case3
	{

	  cerr << "void MultiHist::GetRanges()" << endl;
	  cerr << "  xmin is " << xmin << endl;
	  cerr << "  xmax is " << xmax << endl;
	  cerr << "  Something is wrong.\nProgram is stopped." << endl;
	  exit( -1 );
	}
      else // case2
	{

	  xmax = xmax_;
	  cerr << "=============== WARNING = from here ==============" << endl;
	  cerr << "void MultiHist::GetRange()" << endl;
	  cerr << "xmin is " << xmin << " and xaxis is set as a log scale" << endl;
	  xmin_ = GetSuitableXmin();
	  cerr << "xmin is changed to " << xmin_ << endl;
	  cerr << "=============== WARNING = to here   ==============" << endl;
	}
    }
  else // case1
    {

      xmin_ = xmin;
      xmax_ = xmax;
    }

  if( bl_force_xmin_ == true )
    {

      xmin_ = xmin_force_;
      margin_ratio_left_ = 0.0;
    }

  if( bl_force_xmax_ == true )
    {
      xmax_ = xmax_force_;
      margin_ratio_right_ = 0.0;
    }

  double ymin = *min_element( y.begin(), y.end() );
  double ymax = *max_element( y.begin(), y.end() );

  if( bl_logy_ == true )
    {

      if( ymin <= 0.0 && ymax <= 0.0 )// case4
	{

	  ymin_ = ymin;
	  ymax_ = ymax;
	  gPad->SetLogy( false );
	}
      else if( ymin > 0.0 && ymax <= 0.0 ) // case3
	{

	  cerr << "void MultiHist::GetRanges()" << endl;
	  cerr << "  ymin is " << ymin << endl;
	  cerr << "  ymax is " << ymax << endl;
	  cerr << "  Something is wrong.\nProgram is stopped." << endl;
	  exit( -1 );
	}
      else // case2
	{

	  if( ymin < 0 )
	    {

	      cerr << "=============== WARNING = from here ==============" << endl;
	      cerr << "void MultiHist::GetRange()" << endl;
	      cerr << "ymin is " << ymin << " and yaxis is set as a log scale" << endl;
	      cerr << "ymin is changed to " << ymin_ << endl;
	      cerr << "=============== WARNING = to here   ==============" << endl;
	    }

	  ymax_ = ymax;
	  ymin_ = GetSuitableYmin();

	}
    }
  else // case1
    {

      ymin_ = ymin;
      ymax_ = ymax;
    }

  if( bl_force_ymin_ == true )
    {
      ymin_ = ymin_force_;
      margin_ratio_bottom_ = 0.0;
    }
    
  if( bl_force_ymax_ == true )
    {
      ymax_ = ymax_force_;
      margin_ratio_top_ = 0.0;
    }
}

void MultiHist::Ranges2D()
{

  double bin_num_x = vhist2d_[0]->GetNbinsX();
  double bin_num_y = vhist2d_[0]->GetNbinsY();
  double width_x = vhist2d_[0]->GetXaxis()->GetBinWidth(0);
  double width_y = vhist2d_[0]->GetYaxis()->GetBinWidth(0);

  xmin_ = vhist2d_[0]->GetXaxis()->GetBinCenter(0)         - width_x/2;
  xmax_ = vhist2d_[0]->GetXaxis()->GetBinCenter(bin_num_x) - width_x/2;
  ymin_ = vhist2d_[0]->GetYaxis()->GetBinCenter(0)         - width_y/2;
  ymax_ = vhist2d_[0]->GetYaxis()->GetBinCenter(bin_num_y) - width_y/2;

  if( bl_force_xmin_ )
    xmin_ = xmin_force_;

  if( bl_force_xmax_ )
    xmax_ = xmax_force_;
  
  if( bl_force_ymin_ )
    ymin_ = ymin_force_;

  if( bl_force_ymax_ )
    ymax_ = ymax_force_;

}


////////////////////////////////////////////////////////////
// public functions ////////////////////////////////////////
////////////////////////////////////////////////////////////

void MultiHist::Add( TH1* hist )
{
  /*
    TH1I, F, D 等をまとめて扱えるように，引数を TH1 にして，
    とりあえず TH1D にキャストした。
    今のとこおかしい点はないけど，TH1I で割り算をすると小数点以下が
    切り捨てられる等の癖をどう扱うのかよくわかんない。
    今は TH1D しか使わないから問題ないので放置しておく。    
   */
  vhist_.push_back( (TH1D*)hist ); 
}

void MultiHist::Add( TH2D* hist2d )
{
  vhist2d_.push_back( hist2d );
}

void MultiHist::DeleteAllHist()
{
  DeleteHist();
  DeleteHist2D();
}

void MultiHist::DeleteHist()
{

  vhist_.erase( vhist_.begin() , vhist_.end() );
}

void MultiHist::DeleteHist2D()
{

  vhist2d_.erase( vhist2d_.begin() , vhist2d_.end() );
}

void MultiHist::Draw( string option )
{

  if( stats_type_ == 0 )
    Draw( option, stats_xmin_ , stats_ymin_ , stats_xmax_ , stats_ymax_ );
  else if( stats_type_ == 1 )
    {

      double xmin = stats_xmax_ - stats_width_ ;//* vhist_.size();
      double ymin = stats_ymax_ - stats_height_ * vhist_.size();
      Draw( option, xmin, ymin, stats_xmax_ , stats_ymax_ );
    }

}

void MultiHist::Draw( string option,
		      double stats_xmin, double stats_ymin,
		      double stats_xmax, double stats_ymax )
{

  DrawFrame();

  if( option == "" )
    option = option_;

  option = Replace( option , "sames" , "" );
  option = Replace( option , "SAMES" , "" );
  option = Replace( option , "same"  , "" );
  option = Replace( option , "SAME"  , "" );

  // configuration for stats box
  double stats_height = (stats_ymax - stats_ymin) / vhist_.size();

  for( int i=0; i<vhist_.size(); i++ )
    {
	  
      if( bl_stats_ == true )
	{
	      
	  vhist_[i]->Draw( (option + "SAMES" ).c_str() );

	  // if this is ratio mode, draw stats box
	  if( bl_ratio_mode_ == false )
	    {
	      DrawStats( vhist_[i] , 
			 stats_xmin , stats_ymax - stats_height * (i+1) ,
			 stats_xmax , stats_ymax - stats_height * i 
			 );
	    }
	  else
	    {
	      DrawStats( vhist_[i] , 10, 11 , 10, 11 );
	    }

	  
	}
      else
	{
	  vhist_[i]->Draw( (option + "SAME" ).c_str() );
	}
	  
      if( i==0 && bl_title_==true )
	DrawTitle( title_size_ , title_align_ );
      else if( bl_title_ == false )
	DrawTitle( 9999, 9999 );

    }

  id_++;
}

void MultiHist::DrawFrame()
{

  Ranges();
  Margins();

  double margin_right  = ( xmax_ - xmin_ ) * margin_ratio_right_;
  double margin_left   = ( xmax_ - xmin_ ) * margin_ratio_left_;
  double margin_top    = ( ymax_ - ymin_ ) * margin_ratio_top_;
  double margin_bottom = ( ymax_ - ymin_ ) * margin_ratio_bottom_;

  margin_right_  = margin_right;
  margin_left_   = margin_left;
  margin_top_    = margin_top;
  margin_bottom_ = margin_bottom;

  string name = name_ + title_ + "hframe" + Int2String( id_ );
  id_++;
  TH1F* frame = new TH1F( name.c_str() ,
			  title_.c_str() ,
			  1000, xmin_ - margin_left,
			  xmax_ + margin_right );

  FrameSetting( frame , margin_bottom, margin_top );
  frame->Draw();
 
  if( bl_ratio_mode_ )
    {
      TLine* line = new TLine( xmin_, 1.0, xmax_, 1.0 );
      line->SetLineColor( kRed );
      line->SetLineWidth( 2 );
      line->SetLineStyle( 2 );
      line->Draw();

      // remove bins which contain 0 entry
      for( int i=0; i<vhist_.size(); i++ )
	{

	  for( int j=1; j<vhist_[i]->GetNbinsX()+1; j++)
	    {

	      if( vhist_[i]->GetBinContent( j ) == 0 )
		vhist_[i]->SetBinContent(j, -1 );
	    }
	}

    }

}


void MultiHist::Draw2D( string option )
{

  if( stats_type_ == 0 )
    Draw2D( option, stats_xmin_ , stats_ymin_ , stats_xmax_ , stats_ymax_ );
  else if( stats_type_ == 1 )
    {

      double xmin = stats_xmax_ - stats_width_ ;//* vhist_.size();
      double ymin = stats_ymax_ - stats_height_ * vhist2d_.size();
      Draw2D( option, xmin, ymin, stats_xmax_ , stats_ymax_ );
    }

}

void MultiHist::Draw2D( string option,
			double stats_xmin, double stats_ymin,
			double stats_xmax, double stats_ymax )
{
  
  // temp 
  Ranges2D();
  double margin_right  = ( xmax_ - xmin_ ) * margin_ratio_right_;
  double margin_left   = ( xmax_ - xmin_ ) * margin_ratio_left_;
  double margin_top    = ( ymax_ - ymin_ ) * margin_ratio_top_;
  double margin_bottom = ( ymax_ - ymin_ ) * margin_ratio_bottom_;
  
  if( bl_force_xmax_ )
    margin_right = 0;
  if( bl_force_xmin_ )
    margin_left = 0;
  if( bl_force_ymax_ )
    margin_top = 0;
  if( bl_force_ymin_ )
    margin_bottom = 0;

  string name = name_ + title_ + "hframe" + Int2String( id_ );
  TH1F* frame = new TH1F( name.c_str() , title_.c_str() , 1000, xmin_ - margin_left, xmax_ + margin_right );

  FrameSetting( frame , margin_bottom, margin_top );
  frame->Draw();

  string option2 = "";
  if( bl_stats_ == true )
    option2 = "SAMES";
  else
    option2 = "SAME";

  double stats_height = (stats_ymax - stats_ymin) / vhist2d_.size();

  for( int i=0; i<vhist2d_.size(); i++ )
    {
      vhist2d_[i]->Draw( (option + option2 ).c_str() );

      if( bl_stats_ == true )
	{	

	  if( bl_ratio_mode_ == false )
	    {
	      DrawStats( vhist2d_[i] , 
			 stats_xmin  , stats_ymax - stats_height * (i+1) ,
			 stats_xmax  , stats_ymax - stats_height * i
			 );
	    }
	  else
	    {
	      DrawStats( vhist2d_[i], 10, 11, 10, 11 );
	    }
	}
      if( i == 0 && bl_draw_palette_axis_ == true )
	DrawPaletteAxis( vhist2d_[i] , 0.905, 0.1, 0.93, 0.9, 0.08 );
      else if( i == 0 && bl_draw_palette_axis_ == false )
	DrawPaletteAxis( vhist2d_[i] , 999, 999, 9999, 9999, 0.08 );

      if( i==0 && bl_title_==true )
	DrawTitle( title_size_ , title_align_ );
      else if( bl_title_ == false )
	DrawTitle( 9999, 9999 );

    }  
  
  id_++;
}

void MultiHist::SetMarginV( double ratio )
{
    
  SetMarginTop   ( ratio );
  SetMarginBottom( ratio );
};
  
void MultiHist::SetMarginH( double ratio )
{
  SetMarginLeft ( ratio );
  SetMarginRight( ratio );
};

void MultiHist::SetMargins( double ratio )
{
  SetMarginH( ratio );
  SetMarginV( ratio );
}

void MultiHist::SetStatsBoxSize( double width , double height )
{
  
  stats_width_ = width;
  stats_height_ = height;  
}

void MultiHist::SetStatsBoxPoint( double xmax , double ymax )
{
  stats_xmax_ = xmax;
  stats_ymax_ = ymax;
}

void MultiHist::SetStatsPosition( double xmin, double ymin, double xmax, double ymax )
{

  stats_xmin_ = xmin;
  stats_ymin_ = ymin;
  stats_xmax_ = xmax;
  stats_ymax_ = ymax;
}

void MultiHist::SetStatsFormat( int type )
{
  stats_format_ = type ;
  gStyle->SetOptStat( stats_format_ );
}
void MultiHist::SetStatsType( string type )
{

  if( type == "area" || type == "Area" || type == "AREA" )
    SetStatsType( 0 );
  else if( type == "box" || type == "Box" || type == "BOX" )
    SetStatsType( 1 );
  else 
    SetStatsType( -1 );

}

void MultiHist::SetRange( double xmin, double ymin, double xmax, double ymax )
{
  SetXmin( xmin );
  SetYmin( ymin );
  SetXmax( xmax );
  SetYmax( ymax );
}

void MultiHist::ResetRange()
{

  xmin_force_ = ymin_force_ = xmax_force_ = ymax_force_
    = -9999.9;

  bl_force_xmin_ = bl_force_xmax_ = bl_force_ymin_ = bl_force_ymax_ 
    = false;
}

void MultiHist::SetXmin( double val )
{
  xmin_force_ = val;
  bl_force_xmin_ = true;
};

void MultiHist::SetXmax( double val )
{
  xmax_force_ = val;
  bl_force_xmax_ = true;
};

void MultiHist::SetYmin( double val )
{
  ymin_force_ = val;
  bl_force_ymin_ = true;
};

void MultiHist::SetYmax( double val )
{
  ymax_force_ = val;
  bl_force_ymax_ = true;
};

void MultiHist::Print()
{

  int width = 15;
  cout << setw(width) << "name"   << ":" << name_   << endl;
  cout << setw(width) << "title"  << ":" << title_  << endl;
  cout << setw(width) << "option" << ":" << option_ << endl;
  cout << setw(width) << "x & margin(%)" << ":"
       << setw(width) << setprecision(5) << xmin_ << " - " << margin_ratio_left_ << " <==> "
       << setw(width) << setprecision(5) << xmax_ << " - " << margin_ratio_right_
       << endl;
  cout << setw(width) << "y & margin(%)" << ":"
       << setw(width) << setprecision(5) << ymin_ << " - " << margin_ratio_bottom_ << " <==> "
       << setw(width) << setprecision(5) << ymax_ << " - " << margin_ratio_top_
       << endl;
}
