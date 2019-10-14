#ifndef __CINT__
#include "GraphOperation.hh"
#endif

void AddPoint( TGraph* g_original, TGraph* g_new )
{

  for( int i=0; i<g_new->GetN(); i++ )
    {
      double tempx, tempy;
      g_new->GetPoint( i , tempx, tempy );

      g_original->SetPoint( g_original->GetN(), tempx, tempy );
    }

}

TH1D* GetCommonFrame( vector < TGraph* >& vgraph ,
		      double margin_top = 0.1  , double margin_right = 0.1 ,
		      double margin_bottom = 0.1 , double margin_left = 0.1 )
{

  double xmin = GetMinX( vgraph );
  double xmax = GetMaxX( vgraph );
  double width = xmax - xmin;
  xmin = xmin - width * margin_left;
  xmax = xmax + width * margin_right;

  double ymin = GetMinY( vgraph );
  double ymax = GetMaxY( vgraph );

  double height = fabs( ymax - ymin );
  ymin = ymin - height * margin_bottom;
  ymax = ymax + height * margin_top;
  
  stringstream ss_frame_name;
  ss_frame_name << "common_frame_ " << common_frame_id;

  TH1D* frame = new TH1D( ss_frame_name.str().c_str()  , "" , 10, xmin , xmax );
  frame->SetMaximum( ymax );
  frame->SetMinimum( ymin );

  frame->GetXaxis()->CenterTitle( true );
  frame->GetYaxis()->CenterTitle( true );
  frame->SetStats( false );

  frame->SetBinContent( 12 , 1 );
  //  frame->SetDrawOption( "P" );
  common_frame_id++;
  return frame;
}

/*
TH1D* GetCommonFrame( TGraph** graphs , int num )
{
  return GetCommonFrame( graphs , num , 0.1, 0.1, 0.1, 0.1 );
}
*/

TH1D* GetCommonFrame( TGraph** graphs , int num,
		      double margin_top = 0.1  , double margin_right = 0.1 ,
		      double margin_bottom = 0.1 , double margin_left = 0.1 )
{
  vector < TGraph* > vgraph;
  for( int i=0; i<num; i++ )
    vgraph.push_back( graphs[i] );

  return GetCommonFrame( vgraph, margin_top, margin_right, margin_bottom, margin_left  );
}

/*
TH1D* GetCommonFrame( vector < TGraph* >& vgraph )
{
  return GetCommonFrame( vgraph , 0.1 , 0.1 );
}

TH1D* GetCommonFrame( vector < TGraph* >& vgraph , double vmargin , double hmargin )
{
  return GetCommonFrame( vgraph , vmargin , hmargin , vmargin , hmargin );
}
*/



double GetCorrespond_Core( TGraph* g , double val, string type )
{

  vector < double > vval, vdiff;
  for( int i=0; i<g->GetN(); i++ )
    {

      double temp_target, temp;

      if( type == "x" || type == "X" )
	g->GetPoint( i, temp_target, temp );
      else if( type == "y" || type == "Y" )
	g->GetPoint( i, temp, temp_target );

      if( temp_target == val )
	return temp_target;

      vval.push_back( temp_target );
      vdiff.push_back( fabs( temp_target - val ) );
    }

  int index = min_element( vdiff.begin(), vdiff.end()) - vdiff.begin();
  return vval[index];
}



double GetCorrespondX( TGraph* g , double y )
{
  return GetCorrespond_Core( g , y , "x" );
}

double GetCorrespondY( TGraph* g , double x )
{
  return GetCorrespond_Core( g , x , "y" );
}

TGraph* GetGraph( string graph_name, string graph_title,
		  TTree* tr , string target , string cut )
{

  int data_num = tr->Draw( target.c_str() , cut.c_str() , "goff" );
  TGraph* g = new TGraph( data_num , tr->GetV2() , tr->GetV1() );
  g->SetName( graph_name.c_str() );
  g->SetTitle( graph_title.c_str() );

  GraphSetting( g , kBlack , 2 , 20 , 0 );

  return g;
}

//////////////////////////////////////////////////////
// GetMax

int GetMaxPoint( TGraph* g , double& x, double& y, int mode )
{
  vector < double > vx = GetValX( g );
  vector < double > vy = GetValY( g );

  int index = -1 ;

  if( mode == 0 )
    {
      index = (int)( max_element(vx.begin(), vx.end()) - vx.begin());
    }
  else if( mode == 1 )
    {
      index = (int)( max_element(vy.begin(), vy.end()) - vy.begin());
    }
  else if( mode == 2 )
    {
      vector < double > vr;
      for( int i=0; i<vx.size(); i++ )
	{
	  vr.push_back( pow(vx[i], 2) + pow(vy[i], 2) );
	}
      index = (int)( max_element(vr.begin(), vr.end()) - vr.begin());
    }
  
  x = vx[ index ];
  y = vy[ index ];
  
  return index;
}

int GetMaxXPoint( TGraph* g, double& x, double& y )
{

  return GetMaxPoint(g, x, y, 0 );
}
						  
int GetMaxYPoint( TGraph* g, double& x, double& y )
{
  return GetMaxPoint(g, x, y, 1 );
}
						  
int GetMaxRPoint( TGraph* g, double& x, double& y )
{
  return GetMaxPoint(g, x, y, 2 );
}
						  
double GetMax( TGraph* g , int num )
{

  vector < double > vval = GetVal( g , num );
  return *max_element( vval.begin(), vval.end() );
}

double GetMax( vector < TGraph* >  vg , int num )
{
  vector < double > vmax;
  for( int i=0; i<vg.size(); i++ )
    vmax.push_back( GetMax( vg[i] , num ) );

  return *max_element( vmax.begin() , vmax.end() );
}

double GetMaxX( TGraph* g )
{
  return GetMax( g , 0 );
}

double GetMaxX( vector < TGraph* >  vg )
{
  return GetMax( vg , 0 );
}

double GetMaxY( TGraph* g )
{
  return GetMax( g , 1 );
}

double GetMaxY( vector < TGraph* >  vg )
{
  return GetMax( vg , 1 );
}

//////////////////////////////////////////////////////
// GetMean

double GetMean( TGraph* g , int num )
{

  vector < double > vval = GetVal( g , num );
  return GetMean<double>( vval );
}

double GetMeanX( TGraph* g )
{
  return GetMean( g , 0 );
}

double GetMeanY( TGraph* g )
{
  return GetMean( g , 1 );
}

//////////////////////////////////////////////////////
// GetMin
int GetMinPoint( TGraph* g , double& x, double& y, int mode )
{
  vector < double > vx = GetValX( g );
  vector < double > vy = GetValY( g );

  int index = -1 ;

  if( mode == 0 )
    {
      index = (int)( min_element(vx.begin(), vx.end()) - vx.begin());
    }
  else if( mode == 1 )
    {
      index = (int)( min_element(vy.begin(), vy.end()) - vy.begin());
    }
  else if( mode == 2 )
    {
      vector < double > vr;
      for( int i=0; i<vx.size(); i++ )
	{
	  vr.push_back( pow(vx[i], 2) + pow(vy[i], 2) );
	}
      index = (int)( min_element(vr.begin(), vr.end()) - vr.begin());
    }
  
  x = vx[ index ];
  y = vy[ index ];
  
  return index;
}

double GetMin( TGraph* g , int num )
{

  vector < double > vval = GetVal( g , num );
  return *min_element( vval.begin(), vval.end() );
}

double GetMin( vector < TGraph* >  vg , int num )
{

  vector < double > vmin;
  for( int i=0; i<vg.size(); i++ )
    vmin.push_back( GetMin( vg[i] , num ) );

  return *min_element( vmin.begin() , vmin.end() );
}

double GetMinX( TGraph* g )
{
  return GetMin( g , 0 );
}

double GetMinX( vector < TGraph* >  vg )
{
  return GetMin( vg , 0 );
}

double GetMinY( TGraph* g )
{
  return GetMin( g , 1 );
}

double GetMinY( vector < TGraph* >  vg )
{
  return GetMin( vg , 1 );
}

//////////////////////////////////////////////////////
// GetStdDev

double GetStdDev( TGraph* g , int num )
{

  vector < double > vval = GetVal( g , num );
  return GetStdDev<double>( vval );
}

double GetStdDevX( TGraph* g )
{
  return GetStdDev( g, 0 );
}

double GetStdDevY( TGraph* g )
{
  return GetStdDev( g, 1 );
}

vector < double > GetVal( TGraph* g , int num )
{
  const int kData_num = g->GetN();
  vector < double> vrtn;

  double* val;
  if( num == 0 )
    val = g->GetX();
  else if( num == 1 )
    val = g->GetY();

  for( int i=0; i<kData_num; i++ )
    vrtn.push_back( val[i] );

  return vrtn;
}

vector < double > GetValX( TGraph* g )
{
  return GetVal( g , 0 );
}

vector < double > GetValY( TGraph* g )
{
  return GetVal( g , 1 );
}

TGraph* Subtract( TGraph* g1 , TGraph* g2, int mode )
{

  assert( g1->GetN() == g2->GetN() );

  vector < double > vx, vy;
  for( int i=0; i<g1->GetN(); i++ )
    {

      double dtemp_x1, dtemp_x2, dtemp_y1, dtemp_y2;
      g1->GetPoint( i , dtemp_x1, dtemp_y1 );
      g2->GetPoint( i , dtemp_x2, dtemp_y2 );


      // ( dx , y ) mode
      if( mode == 0 )
	{

	  vx.push_back( dtemp_x1 - dtemp_x2 );
	  vy.push_back( dtemp_y1 );
	}
      // ( x , dy ) mode
      else if( mode == 1 )
	{
	  
	  vx.push_back( dtemp_x1 );
	  vy.push_back( dtemp_y1 - dtemp_y2 );
	}
      // ( dx , dy ) mode
      else if( mode == 2 )
	{
	  vx.push_back( dtemp_x1 - dtemp_x2 );
	  vy.push_back( dtemp_y1 - dtemp_y2 );

	}
    }

  TGraph* g_subtract = new TGraph( vx.size(), &vx[0], &vy[0] );
  GraphSetting( g_subtract );
  return g_subtract;
}

TGraph* SubtractX( TGraph* g1, TGraph* g2 )
{
  return Subtract( g1, g2, 0 );
}

TGraph* SubtractY( TGraph* g1, TGraph* g2 )
{
  return Subtract( g1, g2, 1 );
}


TGraph* Scale( TGraph* g, double factor, int mode )
{
  TGraph* rtn = (TGraph*)g->Clone();
  for( int i=0; i<rtn->GetN(); i++ )
    {
      double x, y;
      rtn->GetPoint( i, x, y );

      if( mode == 0 )
	rtn->SetPoint( i, x * factor, y );
      else if( mode == 1 )
	rtn->SetPoint( i, x, y * factor);
      else if( mode == 2 ) // will I use?
	rtn->SetPoint( i, x * factor, y * factor);

    }

  return rtn;
}

TGraph* ScaleX( TGraph* g, double factor )
{
  return Scale( g, factor, 0 );
}

TGraph* ScaleY( TGraph* g, double factor )
{
  return Scale( g, factor, 1 );
}
