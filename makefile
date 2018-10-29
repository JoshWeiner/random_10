all: randfile.o
	gcc -o go randfile.o

randfile.o: randfile.c randfile.h
	gcc -c randfile.c randfile.h

run:
	./go

clear:
	rm go
	rm *.o
	rm test.txt
