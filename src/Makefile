COMPILER = g++
#COMPILER = clang++
#COMPILER = g++-4.4
CFLAGS    = -g -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal -std=c++11 -O -O1
CFLAGS   += `root-config --cflags`

UNAME := $(shell uname)

ifeq (\$(UNAME),Linux)
CFLAGS_SHARE = -shared 
SUFFIX = .so
endif

ifeq ($(UNAME) , Darwin)
CFLAGS_SHARE = -dynamiclib -fno-common
SUFFIX = .dylib
endif

CFLAGS_SHARE += -fPIC

LDFLAGS   =
LDFLAGS  += `root-config --libs`
INCLUDE   = -I../include

SOURCES  = $(wildcard *.cc)
OBJECTS  = $(SOURCES:.cc=.o)
SHARED_OBJ = $(addprefix lib,$(SOURCES:.cc=$(SUFFIX)))


#lib%.so: %.cc
#	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

ifeq ($(UNAME),Darwin)
lib%.dylib: %.cc
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)
endif

all: clean $(SHARED_OBJ)

install:
	install -s $(SHARED_OBJ) ../lib

clean:
	rm -f -r $(SHARED_OBJ) *~ \#* lib*.dSYM
