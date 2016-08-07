# g++ installed via macports or homebrew on Mac cannot handle -std=c++11 option.
# /usr/bin/g++ on Mac can do this.

COMPILER = g++
#COMPILER = clang++
CFLAGS    = #-g -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal # for warning
CFLAGS   += -std=c++11
CFLAGS   +=  -O -O1 # for optimazation
CFLAGS   += `root-config --cflags`
MYLIB_FLAGS = `MyLibrary-config`

UNAME := $(shell uname)

ifeq ($(UNAME) , Linux)
CFLAGS_SHARE = -shared 
SUFFIX = .so
INSTALL_OPTION = -s
endif

ifeq ($(UNAME) , Darwin)
CFLAGS_SHARE = -dynamiclib -fno-common
SUFFIX = .dylib
INSTALL_OPTION = 
endif

CFLAGS_SHARE += -fPIC

LDFLAGS   =
LDFLAGS  += `root-config --libs`
INCLUDE   = -I../include

SOURCES  = $(wildcard *.cc)
OBJECTS  = $(SOURCES:.cc=.o)
SHARED_OBJ = $(addprefix lib,$(SOURCES:.cc=$(SUFFIX)))

all: $(SHARED_OBJ) MyLibrary.hh

lib%$(SUFFIX): %.cc ../include/%.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

libDirectoryOperation$(SUFFIX): DirectoryOperation.cc StringOperation.cc ../include/DirectoryOperation.hh ../include/StringOperation.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) $(LDFLAGS) -o $@  $<  StringOperation.cc

libMultiHist$(SUFFIX): MultiHist.cc PaveOperation.cc StringOperation.cc ../include/MultiHist.hh ../include/PaveOperation.hh ../include/StringOperation.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) $(LDFLAGS) -o $@  $< PaveOperation.cc StringOperation.cc	

libHistOperation$(SUFFIX): HistOperation.cc Style.cc ../include/HistOperation.hh ../include/Style.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) $(LDFLAGS) -o $@  $< Style.cc

MyLibrary.hh:../include/MyLibrary.hh
	../MakeHeaderFile.sh .. 

install: all
	install $(INSTALL_OPTION) $(SHARED_OBJ) ../lib

clean:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM *.o

clean2:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM ../lib/* *.o
