#include "MultiHist.hh"

using namespace std;

// private function 

// // Initialization
void MultiHist::Init( string name, string title )
{

  name_  = name;
  title_ = title;

  xmin_  = ymin_ = 1.0;
  xmax_  = ymax_ = 2.0;
  margin_ratio_top_ = margin_ratio_bottom_ = margin_ratio_left_ = margin_ratio_right_ = 0.01;
  title_size_ = 0.07;

  bl_stats_ = bl_title_ = bl_draw_no_entry_ 
    = true;

  bl_force_xmin_ = bl_force_xmax_ = bl_force_ymin_ = bl_force_ymax_
    = false;
    
  bl_logx_ = gPad->GetLogx();
  bl_logy_ = gPad->GetLogy();
}

void MultiHist::GetRanges()
{
  vector < double > x, y;
  for( int i=0; i<vhist.size(); i++ )
    {

      int bin = vhist[i]->GetXaxis()->GetNbins();
      double width = vhist[i]->GetBinWidth(i);
	
      if( bl_draw_no_entry_ == true )
	{
	  x.push_back( vhist[i]->GetBinCenter(0)   - width/2. );
	  x.push_back( vhist[i]->GetBinCenter(bin) + width/2. );
	}

      /*
      // not ready
      else
      {

      }
      */
	
      y.push_back( vhist[i]->GetBinContent( vhist[i]->GetMinimumBin() ) );
      y.push_back( vhist[i]->GetBinContent( vhist[i]->GetMaximumBin() ) );

    }

  double xmin = *min_element( x.begin(), x.end() );
  double xmax = *max_element( x.begin(), x.end() );
  if( bl_logx_ == true && xmin < 0 )
    xmin = 1e-5;

  if( bl_force_xmin_ == false )
    {
      xmin_ = xmin;
      margin_ratio_left_ = 0.0;
    }

  if( bl_force_xmax_ == false )
    {
      xmax_ = xmax;
      margin_ratio_right_ = 0.0;
    }

  double ymin = *min_element( y.begin(), y.end() );
  double ymax = *max_element( y.begin(), y.end() );

  if( bl_logy_ == true && ymin < 0 )
    ymin = 1e-5;

  if( bl_force_ymin_ == false )
    {
      ymin_ = ymin;
      margin_ratio_bottom_ = 0.0;
    }
    
  if( bl_force_ymax_ == false )
    {
      ymax_ = ymax;
      margin_ratio_top_ = 0.0;
    }
}


// public function

void MultiHist::Add( TH1* hist )
{
  vhist.push_back( (TH1D*)hist );
}

void MultiHist::Draw( string option )
{
  Draw( option, 0.9, 0.1, 1.0, 0.9 );
}

void MultiHist::Draw( string option,
		      double stats_xmin, double stats_ymin,
		      double stats_xmax, double stats_ymax )
{

  GetRanges();

  double margin_right  = ( xmax_ - xmin_ ) * margin_ratio_right_;
  double margin_left   = ( xmax_ - xmin_ ) * margin_ratio_left_;
  double margin_top    = ( ymax_ - ymin_ ) * margin_ratio_top_;
  double margin_bottom = ( ymax_ - ymin_ ) * margin_ratio_bottom_;

  if( bl_force_xmin_ == false )
    {
      if( bl_logx_ == true && xmin_ - margin_left <= 0 )
	{
	  if( xmin_ == 0 )
	    margin_left = -1e-0;
	  else
	    margin_left = xmin_ - 1e-5;
	}
    }
    
  if( bl_force_ymin_ == false )
    {
      if( bl_logy_ == true && ymin_ - margin_bottom <= 0 )
	{
	  if( ymin_ == 0 )
	    margin_bottom = -1e-0;
	  else
	    margin_bottom = ymin_ - 1e-5;
	    
	}
    }
    
  TH1F* frame = new TH1F( "hframe", title_.c_str() , 1000, xmin_ - margin_left, xmax_ + margin_right );
  frame->SetMinimum( ymin_ - margin_bottom );
  frame->SetMaximum( ymax_ + margin_top );
  frame->SetStats( false );
  frame->GetXaxis()->CenterTitle( true );
  frame->GetYaxis()->CenterTitle( true );
  frame->Draw();

  double stats_height = (stats_ymax - stats_ymin) / vhist.size();
  for( int i=0; i<vhist.size(); i++ )
    {
	
      if( bl_stats_ == true )
	{

	  vhist[i]->Draw( (option + "SAMES" ).c_str() );
	    
	  DrawStats( vhist[i] , 
		     stats_xmin ,  
		     stats_ymax - stats_height * (i+1) ,
		     stats_xmax,
		     stats_ymax - stats_height * i );
	}
      else
	{
	  vhist[i]->Draw( (option + "SAME" ).c_str() );
	}

      if( i==0 && bl_title_==true )
	//	  DrawTitle( gPad , title_size_ );
	DrawTitle( title_size_ );
    }
    
    
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

void MultiHist::SetXmin( double val )
{
  xmin_ = val;
  bl_force_xmin_ = true;
};

void MultiHist::SetXmax( double val )
{
  xmax_ = val;
  bl_force_xmax_ = true;
};

void MultiHist::SetYmin( double val )
{
  ymin_ = val;
  bl_force_ymin_ = true;
};

void MultiHist::SetYmax( double val )
{
  ymax_ = val;
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
