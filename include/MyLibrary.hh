#ifndef MYLIB_MYLIBRARY_HH
#define MYLIB_MYLIBRARY_HH

//include headers
#ifndef __CINT__
#include "CanvasOperation.hh"
#include "CanvasSetting.hh"
#include "HeadersRoot.hh"
#include "HeadersSL.hh"
#include "HistOperation.hh"
#include "IoOperation.hh"
#include "MultiHist.hh"
#include "NumericalOperation.hh"
#include "PaveOperation.hh"
#include "StringOperation.hh"
#include "Style.hh"
#endif // ndef __CINT__

//if __CINT__ is defined, include its source files
#ifdef __CINT__
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/CanvasOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/HistOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/IoOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/MultiHist.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/NumericalOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/PaveOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/StringOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/Style.cc"
#endif // __CINT__
#endif // MYLIB_MYLIBRARY_HH
