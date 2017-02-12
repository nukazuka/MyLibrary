#ifndef __CINT__
#include "TreeOperation.hh"
#endif

#include "TGraph.h"

using namespace std;

vector < double > GetElement(TTree* tr, string target, string cut )
{

  vector < double > vx;

  // as far as I remember, tr->GetEntries() cannot be used due to tr->GetV1()
  const int num = tr->Draw( target.c_str() , cut.c_str(), "goff" );
  double* x = tr->GetV1();

  for( int i=0; i<num; i++ )
    {
      vx.push_back( x[i] );
    }

  return vx;
}

double GetAverageVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );
  return accumulate( vx.begin(), vx.end() , 0.0 ) / (double)vx.size() ;
}

double GetMaxVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );

  if( vx.size() == 0 )
    {
      cerr << "==== WARNING ==================" << endl;
      cerr << "  TreeOperation.cc in MyLibrary" << endl;
      cerr << "  double GetMaxVal( TTree* tr, string target, string cut )" << endl;
      cerr << "  a number of elements with the cut:\n " << cut << " : 0 " << endl;
      cerr << "  1 is returned not to crash program" << endl;
      tr->Print();
      return 1;
    }
  
  return *max_element( vx.begin(), vx.end() );
}

double GetMinVal( TTree* tr, string target, string cut )
{

  vector < double > vx = GetElement( tr, target, cut );
  if( vx.size() == 0 )
    {
      cerr << "==== WARNING ==================" << endl;
      cerr << "  TreeOperation.cc in MyLibrary" << endl;
      cerr << "  double GetMinVal( TTree* tr, string target, string cut )" << endl;
      cerr << "  a number of elements with the cut:\n " << cut << " : 0 " << endl;
      cerr << "  0 is returned not to crash program" << endl;
      return 0;
    }
  
  return *min_element( vx.begin(), vx.end() );
}
