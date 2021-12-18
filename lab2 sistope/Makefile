CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
out = lab2
source = lab2.c Funciones.c 
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
	$(CC) -o bomb bomb.c

clean:
	$(RM) $(out) $(objects) $(depends)

.PHONY: clean
sinclude $(depends)