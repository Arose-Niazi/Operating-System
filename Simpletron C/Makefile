simpletron: simple.o libsimple.a
	gcc -o simpletron.exe simple.o -L. -lsimple
	
libsimple.a: util.o
	ar cr libsimple.a util.o

util.o: util.c
	gcc -c util.c

clean:
	rm simpletron.exe libsimple.a util.o simple.o
