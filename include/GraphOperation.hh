#ifndef MYLIB_GRAPHOPERATION
#define MYLIB_GRAPHOPERATION

#include "HeadersRoot.hh"
#include "HeadersSL.hh"
#include "NumericalOperation.hh"
#include "Style.hh"

using namespace std;

static int common_frame_id = 0;

void AddPoint( TGraph* g_original, TGraph* g_new );

TH1D* GetCommonFrame( TGraph** graphs , int num );

TH1D* GetCommonFrame( TGraph** graphs , int num,
		      double margin_top , double margin_right,
		      double margin_bottom , double margin_left );

TH1D* GetCommonFrame( vector < TGraph* >& vgraph );

TH1D* GetCommonFrame( vector < TGraph* >& vgraph , double vmargin , double hmargin );

TH1D* GetCommonFrame( vector < TGraph* >& vgraph ,
		      double margin_top , double margin_right,
		      double margin_bottom , double margin_left );


double GetCorrespond_Core( TGraph* g , double val, string type = "x" );
double GetCorrespondY( TGraph* g , double x );
double GetCorrespondX( TGraph* g , double y );

TGraph* GetGraph( string graph_name, string graph_title,
		  TTree* tr , string target , string cut );

double GetMax( TGraph* g , int num );
double GetMax( vector < TGraph* >  vg , int num );

double GetMaxX( TGraph* g );
double GetMaxX( vector < TGraph* >  vg );

double GetMaxY( TGraph* g );
double GetMaxY( vector < TGraph* >  vg );

double GetMean( TGraph* g , int num );
double GetMeanX( TGraph* g );
double GetMeanY( TGraph* g );

double GetMin( TGraph* g , int num );
double GetMin( vector < TGraph* >  vg , int num );

double GetMinX( TGraph* g );
double GetMinX( vector < TGraph* >  vg );

double GetMinY( TGraph* g );
double GetMinY( vector < TGraph* >  vg );

double GetStdDev( TGraph* g , int num );
double GetStdDevX( TGraph* g );
double GetStdDevY( TGraph* g );

vector < double > GetVal( TGraph* g , int num );
vector < double > GetValX( TGraph* g );
vector < double > GetValY( TGraph* g );

TGraph* Subtract( TGraph* g1 , TGraph* g2, int mode = 0 );
TGraph* SubtractX( TGraph* g1 , TGraph* g2 );
TGraph* SubtractY( TGraph* g1 , TGraph* g2 );
#endif
