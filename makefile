CC = gcc
CFLAGS = -Wall -g

PROG = main
FONTES = main.c readFile.c
OBJETOS = $(FONTES:.c=.o)

$(PROG): $(OBJETOS)
	gcc $(CFLAGS) $(OBJETOS) -o $@

clean:
	-@ rm -f $(OBJETOS)

depend:
	makedepend -- ${CFLAGS} -- ${FONTES}