### 
## Makefile skeleton
## INFO0030: Projet 3
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
GTK = `pkg-config --cflags --libs gtk+-2.0`
# Files
EXEC=tresor
MODULES=main.c model-treasurehunt.c view-treasurehunt.c controller-treasurehunt.c
OBJECTS=main.o model-treasurehunt.o view-treasurehunt.o controller-treasurehunt.o

## Rules


#
all: $(EXEC)

tresor: $(OBJECTS) doc
	$(LD) -g -o $(EXEC) $(OBJECTS) $(GTK) $(LDFLAGS)

main.o: main.c controller-treasurehunt.h view-treasurehunt.h model-treasurehunt.h
	$(CC) -c main.c -o main.o $(GTK) $(CFLAGS)

model-treasurehunt.o: model-treasurehunt.c model-treasurehunt.h
	$(CC) -c model-treasurehunt.c -o model-treasurehunt.o $(GTK) $(CFLAGS)

view-treasurehunt.o: view-treasurehunt.c view-treasurehunt.h
	$(CC) -c view-treasurehunt.c -o view-treasurehunt.o $(GTK) $(CFLAGS)

controller-treasurehunt.o: controller-treasurehunt.c controller-treasurehunt.h
	$(CC) -c controller-treasurehunt.c -o controller-treasurehunt.o $(GTK) $(CFLAGS)


doc: Doxyfile
	mkdir -p doc
	doxygen Doxyfile

clean:
	rm -f *.o $(EXEC) *~ -rf doc
