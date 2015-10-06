COMPILER = g++
#COMPILER = clang++
#COMPILER = g++-4.4
CFLAGS    = -g -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal # for warning
CFLAGS   += -std=c++11
CFLAGS   +=  -O -O1 # for optimazation
CFLAGS   += `root-config --cflags`

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

lib%.so: %.cc
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

lib%.dylib: %.cc
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

all: $(SHARED_OBJ) MyLibrary.hh

MyLibrary.hh:
	../MakeHeaderFile.sh ..

install:
	install $(INSTALL_OPTION) $(SHARED_OBJ) ../lib

clean:
	rm -rf $(SHARED_OBJ) *~ \#* ../*/*~ *dylib.dSYM
