#ifndef __CINT__
#include "GraphOperation.hh"
#endif


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
/*
{

  vector < double > vy, vdiff;
  for( int i=0; i<g->GetN(); i++ )
    {

      double tempx, tempy;
      g->GetPoint( i, tempx, tempy );
      if( tempx == x )
	return tempy;

      vy.push_back( tempy );
      vdiff.push_back( fabs( tempx - x ) );
    }

  int index = min_element( vdiff.begin(), vdiff.end()) - vdiff.begin();
  return vy[index];

  return -9999.9;
}
*/
