#ifndef __CINT__
#include "NumericalOperation.hh"
#endif

using namespace std;

double Deg2Rad( double degree )
{
  return degree / 180.0 * TMath::Pi();
}

double Rad2Deg( double radian )
{
  return radian / TMath::Pi() * 180.0;
}
