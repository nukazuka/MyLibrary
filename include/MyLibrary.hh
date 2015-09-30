#ifndef MYLIB_MYLIBRARY_HH
#define MYLIB_MYLIBRARY_HH

//include headers
#ifndef __CINT__
#include "CanvasOperation"
#include "CanvasSetting"
#include "HeadersRoot"
#include "HeadersSL"
#include "IoOperation"
#include "MyLibrary"
#include "NumericalOperation"
#include "PaveOperation"
#include "StringOperation"
#include "Style"
#endif // ndef __CINT__

//if __CINT__ is defined, include its source files
#ifdef __CINT__
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/CanvasOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/IoOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/NumericalOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/PaveOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/StringOperation.cc"
#include "/afs/cern.ch/user/g/gnukazuk/private/MyLibrary/src/Style.cc"
#endif // __CINT__
#endif // MYLIB_MYLIBRARY_HH
