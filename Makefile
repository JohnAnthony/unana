FLAGS=--std=c11 -ggdb
.PHONY: clean

all: mkdict unana

mkdict: mkdict.c key.o key.h anagram.o anagram.h
	cc ${FLAGS} mkdict.c key.o anagram.o -o mkdict

unana: unana.c key.o key.h anagram.o anagram.h
	cc ${FLAGS} unana.c key.o anagram.o -o unana

key.o: key.c key.h
	cc ${FLAGS} key.c -c -o key.o

anagram.o: anagram.c anagram.h
	cc ${FLAGS} anagram.c -c -o anagram.o

clean:
	rm -f mkdict unana *.o
