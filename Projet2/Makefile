### 
## Makefile skeleton
## INFO0030: Projet 2
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
AR=ar
RANLIB=ranlib

# Files
EXEC=codebarre
MODULES=main.c pnm.c codeBarre.c
OBJECTS=main.o pnm.o codeBarre.o

## Rules

all: $(EXEC)

codebarre: $(OBJECTS) lib doc test
	$(LD) -g -o $(EXEC) $(OBJECTS) -L libpnm -lpnm -lm $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

codeBarre.o: codeBarre.c
	$(CC) -c codeBarre.c -o codeBarre.o -lm $(CFLAGS)

doc: Doxyfile
	mkdir -p doc
	doxygen Doxyfile

test: lib
	$(LD) -g -o codebarre_test codeBarre.c seatest.c codeBarre_test.c -L libpnm -lpnm -lm $(LDFLAGS)

clean:
	rm -f *.o $(EXEC) *~ -rf doc -r libpnm codebarre_test

#Library
lib: pnm.o
	mkdir -p libpnm
	$(AR) ruv libpnm/libpnm.a pnm.o
	$(RANLIB) libpnm/libpnm.a