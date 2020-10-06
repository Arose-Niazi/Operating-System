simpletron: simple.c libsimple.a
	gcc -o simpletron.exe simple.c -L. -lsimple
	
libsimple.a: util.o
	ar cr libsimple.a util.o

util.o: util.c
	gcc -c util.c

clean:
	rm simpletron.exe libsimple.a util.o simple.o
	
tar:
	tar -cvf FA18_BSE_010_A1.tar simple.c simple.h util.c Makefile
