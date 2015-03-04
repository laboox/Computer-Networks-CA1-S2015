include ../Makefile

all: ca.out
ca.out: main.o
	$(CC) *.o $(CLIBS) -o ca.out 
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
clean:
	rm *.o *.out
