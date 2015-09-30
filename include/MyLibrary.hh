#ifndef MYLIB_MYLIBRARY_HH
#define MYLIB_MYLIBRARY_HH

//include headers
#ifndef __CINT__
#include "CanvasOperation.hh"
#include "CanvasSetting.hh"
#include "HeadersRoot.hh"
#include "HeadersSL.hh"
#include "IoOperation.hh"
#include "NumericalOperation.hh"
#include "PaveOperation.hh"
#include "StringOperation.hh"
#include "Style.hh"
#endif // ndef __CINT__

//if __CINT__ is defined, include its source files
#ifdef __CINT__
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/CanvasOperation.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/CanvasSetting.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/HeadersRoot.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/HeadersSL.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/IoOperation.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/NumericalOperation.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/PaveOperation.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/StringOperation.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../include/Style.hh"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/CanvasOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/IoOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/NumericalOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/PaveOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/StringOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/../src/Style.cc"
#endif // __CINT__
#endif // MYLIB_MYLIBRARY_HH
