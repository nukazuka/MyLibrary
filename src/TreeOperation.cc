#include "TreeOperation.hh"

using namespace std;

vector < double > GetElement(TTree* tr, string target, string cut )
{
  vector < double > vx;
  int num = tr->Draw( target.c_str() , cut.c_str(), "goff" );
  double* x = tr->GetV1();

  for( int i=0; i<num; i++ )
    vx.push_back( x[i] );
  return vx;
}

double GetAverageVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );
  return accumulate( vx.begin(), vx.end() , 0 ) / (double)vx.size() ;
}

double GetMaxVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );
  return *max_element( vx.begin(), vx.end() );
}

double GetMinVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );
  return *min_element( vx.begin(), vx.end() );
}
