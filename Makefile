.PHONY: clean

all: mkdict unana

mkdict: mkdict.c
	cc mkdict.c -o mkdict

unana: unana.c
	cc unana.c -o unana

clean:
	rm mkdict unana
