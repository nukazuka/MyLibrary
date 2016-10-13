#ifndef MYLIB_TREEOPERATION
#define  MYLIB_TREEOPERATION

#include "HeadersSL.hh"
#include "HeadersRoot.hh"
#include <algorithm>

using namespace std;

vector < double > GetElement(TTree* tr, string target, string cut );
double GetAverageVal( TTree* tr, string target, string cut );
double GetMaxVal( TTree* tr, string target, string cut );
double GetMinVal( TTree* tr, string target, string cut );



//#include ".hh"
/*
using namespace std;

template < class T, class T2 >
T* GetHist( TTree* tr, string name, string title,
	    int bin_num, T2 xmin, T2 xmax, 
	    string target, string cut )
{

  T* hist = new T( name.c_str(), title.c_str(), bin_num, xmin, xmax );
  hist->Sumw2();
  tr->Draw( (target+">>"+name).c_str() , cut.c_str() , "goff" );

  return hist;
}
*/

#ifdef __CINT__
#include "../src/TreeOperation.cc"
#endif

#endif
