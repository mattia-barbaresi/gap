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

CC=gcc -std=c99
FLAGS=-Wall -pedantic

ifdef DEBUG
FLAGS+= -pipe -g
else
FLAGS+= -pipe -O3 -march=native -DNDEBUG
endif

all: array_list.o array_stack.o gap.o gap_instance.o hash_set.o main.o util.o
	$(CC) $(FLAGS) array_list.o array_stack.o gap.o gap_instance.o hash_set.o main.o util.o -o main

array_list.o: array_list.h array_list.c util.h
	$(CC) $(FLAGS) array_list.c -c -o array_list.o

array_stack.o: array_stack.h array_stack.c util.h
	$(CC) $(FLAGS) array_stack.c -c -o array_stack.o

clean:
	rm -f *.o main

gap.o: array_list.h array_stack.h gap.h gap.c util.h
	$(CC) $(FLAGS) gap.c -c -o gap.o

gap_instance.o: array_list.h gap_instance.h
	$(CC) $(FLAGS) gap_instance.c -c -o gap_instance.o

hash_set.o: hash_set.h hash_set.c util.h
	$(CC) $(FLAGS) hash_set.c -c -o hash_set.o

indent:
	indent -l120 *.h *.c

main.o: array_list.h gap.h main.c util.h
	$(CC) $(FLAGS) main.c -c -o main.o

util.o: util.h util.c
	$(CC) $(FLAGS) util.c -c -o util.o
