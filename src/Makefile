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

all: clean2 $(SHARED_OBJ) MyLibrary.hh install clean

lib%$(SUFFIX): %.cc ../include/%.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

libDirectoryOperation: DirectoryOperation.cc StringOperation.cc ../include/DirectoryOperation.hh ../include/StringOperation.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) $(LDFLAGS) -o $@  $<  StringOperation.cc

libMultiHist$(SUFFIX): MultiHist.cc PaveOperation.cc StringOperation.cc ../include/MultiHist.hh ../include/PaveOperation.hh ../include/StringOperation.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) $(LDFLAGS) -o $@  $< PaveOperation.cc StringOperation.cc	

MyLibrary.hh:
	../MakeHeaderFile.sh ..

install:
	install $(INSTALL_OPTION) $(SHARED_OBJ) ../lib

clean:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM *.o

clean2:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM ../lib/* *.o
