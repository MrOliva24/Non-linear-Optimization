include options.mk

all: Brent.exe

Brent.exe: main.o Brent.o func.o
	gcc main.o Brent.o func.o -L$(LIBPATH) -lm -lgsl -lgslcblas -o Brent.exe -static

main.o: main.c
	gcc -c main.c -Wall -I$(INCLUDEPATH) -o main.o
Brent.o: Brent.c
	gcc -c Brent.c -Wall -I$(INCLUDEPATH) -o Brent.o
func.o: func.c
	gcc -c func.c -Wall -I$(INCLUDEPATH) -o func.o

clean: 
	$(DELETE) *.o
	$(DELETE) *.exe
