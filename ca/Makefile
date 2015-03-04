include ../Makefile

all: ca.out
ca.out: main.o
	$(CC) *.o $(CLIBS) -o ca.out 
main.o: main.cpp user.o
	$(CC) $(CFLAGS) -c main.cpp
	
clean:
	rm *.o *.out
