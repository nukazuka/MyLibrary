COMPILER = g++
#COMPILER = clang++
#COMPILER = g++-4.4
CFLAGS    = -g -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal -std=c++11 -O -O1
CFLAGS   += `root-config --cflags`
CFLAGS_SHARE = -shared -fPIC
LDFLAGS   =
LDFLAGS  += `root-config --libs`
INCLUDE   = -I../include

SOURCES  = $(wildcard *.cc)
OBJECTS  = $(SOURCES:.cc=.o)
SHARED_OBJ = $(addprefix lib,$(SOURCES:.cc=.so))

lib%.so: %.cc
	$(COMPILER) $(CFLAGS) $(CFLAGS_SHARE) $(INCLUDE) -o $@  $< $(LDFLAGS)

all: clean $(SHARED_OBJ)

install:
	install -s *.so ../lib

clean:
	rm -f $(SHARED_OBJ) *~ \#* 
