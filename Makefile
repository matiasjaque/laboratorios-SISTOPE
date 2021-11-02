CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
out = lab1
source = lab1.c Funciones.c
objects = $(source:.c=.o)
depends = .depends
headers = Funciones.h

$(build): $(out)
$(out): $(objects)
	$(CC) -o $@ $^ $(CFLAGS)

$(objects): 
	$(CC) -c $*.c

$(depends): $(source) $(headers)
	@$(CC) -MM $(source) > $@

clean:
	$(RM) $(out) $(objects) $(depends)

.PHONY: clean
sinclude $(depends)

run:
	./lab1 -a 1 -b 2 -c hola
	./lab1 -a 2 -b 5 -c hola
	./lab1 -a 3 -b 4 -c hola
	./lab1 -a 4 -b 4 -c hola
