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
#include "/Users/nukazuka/local/MyLibrary/src/../src/CanvasOperation.cc"
#include "/Users/nukazuka/local/MyLibrary/src/../src/IoOperation.cc"
#include "/Users/nukazuka/local/MyLibrary/src/../src/NumericalOperation.cc"
#include "/Users/nukazuka/local/MyLibrary/src/../src/PaveOperation.cc"
#include "/Users/nukazuka/local/MyLibrary/src/../src/StringOperation.cc"
#include "/Users/nukazuka/local/MyLibrary/src/../src/Style.cc"
#endif // __CINT__
#endif // MYLIB_MYLIBRARY_HH
