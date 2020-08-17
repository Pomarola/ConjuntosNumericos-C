ARG = -Wall -Wextra -Werror -std=c99
SLIST = ../SList/slist
THASH = ../THash/thash
DLIST = ../DList/dlist
CONJUNTO = ../Conjunto/conjunto
TEMP = $(SLIST).o $(THASH).o $(DLIST).o $(CONJUNTO).o interprete.o

all: interprete

interprete: interprete.c slist.o thash.o dlist.o conjunto.o
	gcc $(ARG) -o interprete interprete.c slist.o thash.o dlist.o conjunto.o -lm

slist.o: $(SLIST).c $(SLIST).h
	gcc $(ARG) -c $(SLIST).c 

thash.o: $(THASH).c $(THASH).h
	gcc $(ARG) -c $(THASH).c 

dlist.o: $(DLIST).c $(DLIST).h
	gcc $(ARG) -c $(DLIST).c 

conjunto.o: $(CONJUNTO).c $(CONJUNTO).h
	gcc $(ARG) -c $(CONJUNTO).c 

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean