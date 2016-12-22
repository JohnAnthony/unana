FLAGS=--std=c11 -Os
.PHONY: clean

all: mkdict unana

mkdict: mkdict.c
	cc ${FLAGS} mkdict.c -o mkdict

unana: unana.c
	cc ${FLAGS} unana.c -o unana

clean:
	rm mkdict unana
