##
## Flags to compile on the MAC
##CXXFLAGS  := -I$(ROOTSYS)/include -Iinclude/ -O2 -pedantic -pipe -Wall -W \
##	     -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long -std=c++1y

## Flags to compile on LXPLUS
CXXFLAGS  := -I$(ROOTSYS)/include -Iinclude/ -O2 -pedantic -pipe -Wall -W \
	     	-Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-long-long \
##		-std=c++11	


CXX     = g++

ROOTLIBS := -L$(ROOTSYS)/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lm -ldl -rdynamic -lMinuit

SRC = $(wildcard src/*.cxx)
OBJECTS := $(patsubst %.cxx, %.o, $(SRC))

all: toy

toy: $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(ROOTLIBS) -o toy

%.o: %.C 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

%.o: %.cxx 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -f toy
	rm -f $(OBJECTS) 	

