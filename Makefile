# This file is part of gap.
#
# gap is free software: you can redistribute it and/or modify
# under the terms of the GNU General Public License as published by
# Free Software Foundation, either version 3 of the License, or
# your option) any later version.
#
# gap is distributed in the hope that it will be useful,
# WITHOUT ANY WARRANTY; without even the implied warranty of
# CHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with gap.  If not, see <http://www.gnu.org/licenses/>.

DEBUG=1
NO_OPENMP=1
NO_SDL=1

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
