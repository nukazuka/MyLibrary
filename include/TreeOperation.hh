#ifndef MYLIB_TREEOPERATION
#define  MYLIB_TREEOPERATION

/*
#ifdef __linux__
#include "/home/gnukazuk/local/MyLibrary/include/MyLibrary.hh"
#elif __APPLE__
#include "/Users/nukazuka/local/MyLibrary/include/MyLibrary.hh"
#endif
*/

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

#endif
