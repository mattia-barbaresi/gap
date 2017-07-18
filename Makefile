# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

##################################################
# CONFIGURE THESE VARIABLES
# or set them on the command line, like:
#   make main DEBUG=1
##################################################

#debug enabled
DEBUG=1

# Uncomment this if you don't want to use OPENMP (OPENMP makes the program parallel)
NO_OPENMP=1

# Uncomment this if you don't have SDL installed (SDL is for graphics)
# SDL is used for the automaton example
NO_SDL=1

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
CXXFLAGS += -Wall -pedantic
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

indent: $(SRCDIR/main.c) $(INCDIR)/
	indent -l120 $(SRCDIR)/main.c $(INCDIR)/*

main: $(SRCDIR)/main.c $(INCDIR)/
	$(CXX) $(CPPFLAGS) $(SRCDIR)/main.c -o $(BINDIR)/main $(CXXFLAGS)
clean:
	rm -f $(BINDIR)/main
