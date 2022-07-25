### 
## Connect-4 Makefile skeleton 
## INFO0030: Projet 4
### 
#-------------
## Variables
#-------------
AR=ar
RANLIB=ranlib
GTK =`pkg-config --cflags --libs gtk+-2.0`
LATEX=pdflatex

#-----------------
## Tools & flags
#-----------------
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wunused-parameter -Wdeprecated-declarations
LD=gcc
LDFLAGS=

#---------
## Rules
#---------

all:  doc puissance4

puissance4: main.o controller-connect4.o view-connect4.o model-connect4.o
	$(LD) -g -o ../puissance4 main.o controller-connect4.o view-connect4.o model-connect4.o $(GTK) $(LDFLAGS)

main.o: main.c controller-connect4.h view-connect4.h model-connect4.h
	$(CC) -g -c main.c -o main.o $(GTK) $(CFLAGS)

model-connect4.o: model-connect4.c model-connect4.h
	$(CC) -g -c model-connect4.c -o model-connect4.o $(GTK) $(CFLAGS)

view-connect4.o: view-connect4.c view-connect4.h
	$(CC) -g -c view-connect4.c -o view-connect4.o $(GTK) $(CFLAGS)

controller-connect4.o: controller-connect4.c controller-connect4.h
	$(CC) -g -c controller-connect4.c -o controller-connect4.o $(GTK) $(CFLAGS)

clean:
	rm -f *.o ../puissance4 
	rm -rf ../doc/html

doc: Doxyfile
	doxygen Doxyfile

