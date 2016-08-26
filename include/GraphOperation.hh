#ifndef MYLIB_GRAPHOPERATION
#define MYLIB_GRAPHOPERATION

#include "HeadersRoot.hh"

using namespace std;

double GetCorrespond_Core( TGraph* g , double val, string type = "x" );
double GetCorrespondY( TGraph* g , double x );
double GetCorrespondX( TGraph* g , double y );

#endif
