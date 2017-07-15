##################################################
# CONFIGURE THESE VARIABLES
# or set them on the command line, like:
#   make main DEBUG=1
##################################################

#debug enabled
DEBUG=1

# Uncomment this if you don't want to use OPENMP (OPENMP makes the program parallel)
#NO_OPENMP = 1

# Uncomment this if you don't have SDL installed (SDL is for graphics)
# SDL is used for the automaton example
#NO_SDL = 1

##################################################

SRCDIR=.
INCDIR=$(SRCDIR)/include
BINDIR=$(SRCDIR)/bin

# set this variable to another compiler, or gcc is the default
CXX = gcc -std=c99

# optimization options
ifdef DEBUG
CXXFLAGS += -pipe -g
else
CXXFLAGS += -g -pipe -O3 -march=native -DNDEBUG
endif

# Correctness options
CXXFLAGS += -Wall
CPPFLAGS += -I$(SRCDIR) -I$(INCDIR)



ifndef NO_OPENMP
CXXFLAGS += -fopenmp
endif

ifdef NO_SDL
CXXFLAGS += -DNO_SDL
else
CXXFLAGS += -lSDL
endif


all: main

main: $(SRCDIR)/main.c $(INCDIR)/
	$(CXX) $(CPPFLAGS)   $(SRCDIR)/main.c -o $(BINDIR)/main $(CXXFLAGS)
clean:
	rm -f $(BINDIR)/main
