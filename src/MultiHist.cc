#include "MultiHist.hh"

using namespace std;

// private function 

// // Initialization
void MultiHist::Init( )
{
  Init( (string)"default_name", (string)"default_title" );
}
void MultiHist::Init( string name, string title )
{

  id_ = stats_type_ = 0;
  name_  = name;
  title_ = title;

  xmin_  = ymin_ = 1.0;
  xmax_  = ymax_ = 2.0;
  margin_ratio_top_ = margin_ratio_bottom_ = margin_ratio_left_ = margin_ratio_right_ = 0.01;

  stats_xmin_ = 0.9;
  stats_ymin_ = 0.1;
  stats_xmax_ = 1.0;
  stats_ymax_ = 0.9;

  stats_width_ = 0.1;
  stats_height_ = 0.1;

  title_size_ = 0.07;

  bl_stats_ = bl_title_ = bl_draw_no_entry_ 
    = true;

  bl_force_xmin_ = bl_force_xmax_ = bl_force_ymin_ = bl_force_ymax_
    = false;
    
  CheckLogScale();
}

void MultiHist::CheckLogScale()
{
  bl_logx_ = gPad->GetLogx();
  bl_logy_ = gPad->GetLogy();
}


void MultiHist::Margins()
{

  //  margin_ratio_top_ = 0.01;

  double diff_x = xmax_ - xmin_;
  double diff_y = ymax_ - ymin_;

  if( bl_logx_ == true  && (xmin_ - diff_x * margin_ratio_left_ ) <= 0 )
    margin_ratio_left_ = xmin_ * 0.5 / diff_x;

  if( bl_logy_ == true  && (ymin_ - diff_y * margin_ratio_left_ ) <= 0 )
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
	
      if( bl_draw_no_entry_ == true )
	{
	  x.push_back( vhist_[i]->GetBinCenter(0)   - width/2. );
	  x.push_back( vhist_[i]->GetBinCenter(bin) + width/2. );
	}

      /*
      // not ready
      else
      {

      }
      */
	
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

// public function

void MultiHist::Add( TH1* hist )
{
  vhist_.push_back( (TH1D*)hist );
}

void MultiHist::DeleteAllHist()
{

  vhist_.erase( vhist_.begin() , vhist_.end() );
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

  Ranges();
  Margins();

  double margin_right  = ( xmax_ - xmin_ ) * margin_ratio_right_;
  double margin_left   = ( xmax_ - xmin_ ) * margin_ratio_left_;
  double margin_top    = ( ymax_ - ymin_ ) * margin_ratio_top_;
  double margin_bottom = ( ymax_ - ymin_ ) * margin_ratio_bottom_;

  string name = name_ + title_ + "hframe" + Int2String( id_ );
  TH1F* frame = new TH1F( name.c_str() , title_.c_str() , 1000, xmin_ - margin_left, xmax_ + margin_right );
  frame->SetMinimum( ymin_ - margin_bottom );
  frame->SetMaximum( ymax_ + margin_top );
  frame->SetStats( false );
  frame->GetXaxis()->CenterTitle( true );
  frame->GetYaxis()->CenterTitle( true );
  frame->Draw();

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
	    
	  DrawStats( vhist_[i] , 
		     stats_xmin ,  
		     stats_ymax - stats_height * (i+1) ,
		     stats_xmax,
		     stats_ymax - stats_height * i );
	}
      else
	{
	  vhist_[i]->Draw( (option + "SAME" ).c_str() );
	}

      if( i==0 && bl_title_==true )
	DrawTitle( title_size_ );
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

void MultiHist::SetStatsType( string type )
{

  if( type == "area" || type == "Area" || type == "AREA" )
    SetStatsType( 0 );
  else if( type == "box" || type == "Box" || type == "BOX" )
    SetStatsType( 1 );
  else 
    SetStatsType( -1 );

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
