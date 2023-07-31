FLAGS=--std=gnu11 -Os
.PHONY: clean

all: mkdict unana

mkdict: mkdict.c key.o key.h
	cc ${FLAGS} mkdict.c key.o -o mkdict

unana: unana.c key.o key.h
	cc ${FLAGS} unana.c key.o -o unana

key.o: key.c key.h
	cc ${FLAGS} key.c -c -o key.o

clean:
	rm -f mkdict unana *.o
