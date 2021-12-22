CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
.DEFAULT_GOAL = build

build: lab2 bomb

lab2: lab2.c
	$(CC) -o lab2 lab2.c $(CFLAGS)

bomb: bomb.c Funciones.h Funciones.o
	$(CC) -o bomb bomb.c Funciones.o $(CFLAGS)

Funciones.o: Funciones.c
	$(CC) -c Funciones.c $(CFLAGS)

clean:
	$(RM) lab2 lab2.o bomb bomb.o Funciones.o  

.PHONY: clean
#sinclude $(depends)