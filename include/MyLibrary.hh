#ifndef MYLIB_MYLIBRARY_HH
#define MYLIB_MYLIBRARY_HH

//include headers
#ifndef __CINT__
#include "CanvasOperation.hh"
#include "CanvasSetting.hh"
#include "GetCanvas.hh"
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
#include "/home/gnukazuk/local/MyLibrary/src/../include/CanvasOperation.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/CanvasSetting.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/GetCanvas.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/HeadersRoot.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/HeadersSL.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/IoOperation.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/NumericalOperation.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/PaveOperation.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/StringOperation.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../include/Style.hh"
#include "/home/gnukazuk/local/MyLibrary/src/../src/CanvasOperation.cc"
#include "/home/gnukazuk/local/MyLibrary/src/../src/IoOperation.cc"
#include "/home/gnukazuk/local/MyLibrary/src/../src/NumericalOperation.cc"
#include "/home/gnukazuk/local/MyLibrary/src/../src/PaveOperation.cc"
#include "/home/gnukazuk/local/MyLibrary/src/../src/StringOperation.cc"
#include "/home/gnukazuk/local/MyLibrary/src/../src/Style.cc"
#endif // __CINT__
#endif // MYLIB_MYLIBRARY_HH
