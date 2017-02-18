.SUFFIXES: .F90

CC=gcc
CFLAGS=-O3
LIBS=-ltcl

.c.o:
	$(CC) $(CFLAGS) -c $<
cubeTool: cubeTool.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
clean:
	@rm -f *.o cubeTool
.PHONY: clean
