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

lib%.so: %.cc ../include/%.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

lib%.dylib: %.cc ../include/%.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

libMultiHist.dylib: MultiHist.cc ../include/MultiHist.hh
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) -L../lib -lPaveOperation $(INCLUDE) -o $@  $< $(LDFLAGS)


MyLibrary.hh:
	../MakeHeaderFile.sh ..

install:
	install $(INSTALL_OPTION) $(SHARED_OBJ) ../lib

clean:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM
